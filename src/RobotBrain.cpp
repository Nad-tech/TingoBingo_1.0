// ============================================================
// ROBOTBRAIN OVERVIEW
// ============================================================
//
// RobotBrain is Tingo's high-level behaviour coordinator.
//
// It acts as the decision-making layer between the robot's
// physical systems and the things happening in the game.
//
// RobotBrain does not draw Tingo or directly perform low-level
// actions. Instead, it keeps track of Tingo's current behaviour,
// emotion, speech, and interactions, then tells the appropriate
// systems what to do.
//
// The main behaviour flow is:
//
//     Idle
//       |
//       | 10 seconds
//       v
//     Searching
//       |
//       | search ray detects object
//       v
//     Reacting
//       |
//       | reaction complete
//       v
//     Idle
//
// RobotBrain also handles:
//
//     - Speech requests and speech state
//     - Tingo's emotional state
//     - Looking at objects
//     - Objects being held by the mouse
//     - Objects detected by the search ray
//     - Search-ray generation and collision detection
//     - Object reaction cooldowns
//     - Behaviour timers
//
// Other systems perform the actual work:
//
//     Robot
//         Handles Tingo's physical and visual behaviour.
//
//     SpeechController
//         Handles speech generation, loading, playback, and
//         completion.
//
//     Object
//         Provides object information and collision boxes.
//
// RobotBrain therefore acts as the coordinator:
//
//     Game events
//          |
//          v
//     RobotBrain
//          |
//          +----> Robot
//          |
//          +----> SpeechController
//          |
//          +----> Object interaction
//
// The brain decides WHAT Tingo should be doing.
// The other systems handle HOW that action is performed.
// ============================================================

#include "RobotBrain.h"
#include "Robot.h"
#include "Input.h"
#include "SpeechController.h"
#include <string>
#include "Emotion.h"
#include <cmath>
#include <iostream>

RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle),
      emotion(Emotion::Neutral),
      targetObject(nullptr),
      detectedObject(nullptr)
{
}


// ============================================================
// SetState
// ============================================================
//
// Changes the brain's current high-level behaviour state.
//
// The state itself does not perform any behaviour here.
//
// For example:
//
//     SetState(State::Searching);
//
// simply changes:
//
//     state = Searching
//
// The actual Searching behaviour is performed later by
// RobotBrain::Update(), which checks the current state every
// frame.
//
// This means SetState() is a simple state setter rather than
// a complete state-transition system.
// ============================================================

void RobotBrain::SetState(State state)
{
    this->state = state;
}


// ============================================================
// SetEmotion
// ============================================================
//
// Changes Tingo's current emotional state.
//
// Most emotions are simply stored:
//
//     emotion = newEmotion;
//
// Happy has an additional side effect. Whenever Happy is
// requested, the happyTimer is reset to zero.
//
// This means that calling SetEmotion(Happy) is not merely
// changing the emotion -- it also restarts the Happy timer.
//
// It is therefore important to remember that repeatedly calling
// SetEmotion(Happy) will repeatedly reset happyTimer.
//
// The current RobotBrain implementation calls SetEmotion(Happy)
// from several behaviours, including while an object is being
// held or detected.
// ============================================================

void RobotBrain::SetEmotion(Emotion newEmotion)
{
    emotion = newEmotion;
}


// ============================================================
// Update
// ============================================================
//
// This is the main RobotBrain update function.
//
// It is called once per frame and coordinates the different
// systems controlled by the brain.
//
// The order here is important because several independent
// sections can change Tingo's state, emotion, gaze, and speech
// during the same update.
//
// The function handles:
//
//     1. SpeechController updates
//     2. Visual speaking state
//     3. Speech completion
//     4. Idle behaviour
//     5. Searching behaviour
//     6. Object reaction cooldown
//     7. Currently-held object behaviour
//     8. Search-detected object behaviour
//
// These are separate if statements rather than one large
// if/else-if state machine.
//
// Therefore a change made earlier in Update() can affect code
// later in the same Update() call.
//
// For example, Search() can change state to Reacting and also
// set detectedObject. Later in this same Update() call, the
// detectedObject block can then process that object.
// ============================================================

void RobotBrain::Update(float dt)
{
    // --------------------------------------------------------
    // Update the speech system first.
    //
    // SpeechController is responsible for managing the speech
    // lifecycle. The brain updates it before checking its state
    // so that the brain is working with the latest information
    // about sound generation/loading/playback.
    // --------------------------------------------------------

    speechController.Update();


    // --------------------------------------------------------
    // SPEECH ACTIVE
    //
    // SoundLoaded() tells the brain that the generated audio
    // now exists and is ready for playback/use.
    //
    // SpeechFinished() must still be false because the speech
    // lifecycle has not completed.
    //
    // This allows the brain to distinguish between a speech
    // request that is still being generated and speech that
    // has progressed far enough to be considered active.
    //
    // When this condition is true:
    //
    //     Robot is marked as speaking.
    //     Tingo becomes Happy.
    //
    // The actual speech generation/playback is handled by
    // SpeechController, not by RobotBrain.
    // --------------------------------------------------------

    if
    (
        speechController.SoundLoaded() &&
        !speechController.SpeechFinished()
    )
    {
        robot.SetSpeaking(true);
        SetEmotion(Emotion::Happy);
    }


    // --------------------------------------------------------
    // SPEECH FINISHED
    //
    // SpeechFinished() represents completion of the speech
    // lifecycle.
    //
    // When speech has completely finished, RobotBrain clears
    // the visual speaking state and returns Tingo's emotion
    // to Neutral.
    //
    // This check is separate from SoundLoaded() because
    // generating/loading a sound and completing playback are
    // different stages of the speech lifecycle.
    // --------------------------------------------------------

    if(speechController.SpeechFinished())
    {
        robot.SetSpeaking(false);
        SetEmotion(Emotion::Neutral);
    }


    // ========================================================
    // IDLE BEHAVIOUR
    // ========================================================
    //
    // Idle is Tingo's normal resting behaviour.
    //
    // While Idle:
    //
    //     - Tingo looks forward.
    //     - idleTimer counts how long Tingo has remained idle.
    //
    // After 10 seconds, Tingo leaves Idle and enters Searching.
    //
    // The timers are reset when the transition happens so that
    // the next Idle/Search cycle starts cleanly.
    // ========================================================

    if(state == State::Idle)
    {
        // Keep Tingo facing forward while nothing else is
        // controlling his gaze.
        robot.LookForward();

        // dt is the amount of time that passed since the
        // previous frame. Adding dt makes the timer independent
        // of frame rate.
        idleTimer += dt;


        // ----------------------------------------------------
        // Transition from Idle to Searching.
        //
        // The search timer is cleared because a new search is
        // about to begin.
        //
        // The idle timer is also cleared so the next time Tingo
        // enters Idle, the ten-second countdown starts again.
        // ----------------------------------------------------

        if(idleTimer >= 10.0f)
        {
            searchTimer = 0.0f;
            idleTimer = 0.0f;

            state = State::Searching;
        }
    }


    // ========================================================
    // SEARCHING BEHAVIOUR
    // ========================================================
    //
    // While Searching, Search() is called every frame.
    //
    // Search() is responsible for:
    //
    //     - advancing the search angle
    //     - creating the search direction
    //     - creating the search ray
    //     - moving Tingo's gaze
    //     - testing objects against the ray
    //
    // searchTimer measures how long the current search has
    // been running.
    //
    // In this implementation the search ends after 5 seconds
    // unless an object is detected first.
    // ========================================================

    if(state == State::Searching)
    {
        searchTimer += dt;

        // Perform one frame of searching.
        //
        // Search() may change the state to Reacting if an
        // object is found.
        Search(dt);


        // ----------------------------------------------------
        // End the search after five seconds.
        //
        // If no object has caused the search to transition into
        // another behaviour, Tingo returns to Idle.
        // ----------------------------------------------------

        if(searchTimer >= 5.0f)
        {
            idleTimer = 0.0f;
            searchTimer = 0.0f;

            state = State::Idle;
        }
    }


    // ========================================================
    // OBJECT REACTION COOLDOWN
    // ========================================================
    //
    // reactionCoolDown prevents Tingo from repeatedly speaking
    // every time an object interaction is triggered.
    //
    // When the cooldown is active, its timer advances.
    //
    // After ten seconds, the cooldown is cleared and another
    // object reaction can trigger speech.
    //
    // The cooldown is separate from the detected-object timer.
    // They control different parts of Tingo's behaviour.
    // ========================================================

    if(reactionCoolDown)
    {
        reactionCoolDownTimer += dt;
    }


    // --------------------------------------------------------
    // Cooldown expiration.
    //
    // Once ten seconds have passed, allow another object
    // reaction and reset the cooldown timer.
    // --------------------------------------------------------

    if(reactionCoolDownTimer >= 10.0)
    {
        reactionCoolDown = false;
        reactionCoolDownTimer = 0;
    }


    // ========================================================
    // CURRENTLY HELD OBJECT
    // ========================================================
    //
    // targetObject represents the object Tingo is currently
    // interacting with, specifically an object that was picked
    // up through the mouse interaction system.
    //
    // This is separate from detectedObject.
    //
    // targetObject:
    //     Object being actively held/interacted with.
    //
    // detectedObject:
    //     Object found by the search ray.
    // ========================================================

    if(targetObject != nullptr)
    {
        // ----------------------------------------------------
        // The object is still being held.
        //
        // Tingo continuously looks at the held object while
        // the mouse is holding it.
        //
        // The state is changed to Reacting because Tingo is
        // actively responding to the object rather than being
        // in a normal Idle state.
        // ----------------------------------------------------

        if(targetObject->IsHeldByMouse())
        {
            robot.LookAt(targetObject->GetPosition());
            SetState(State::Reacting);


            // ------------------------------------------------
            // Ball and banana are currently recognised as
            // objects that make Tingo Happy.
            //
            // SetEmotion(Happy) also resets happyTimer.
            //
            // Because this code runs every frame while the
            // object is held, happyTimer will also be reset
            // every frame during this interaction.
            // ------------------------------------------------

            if
            (
                targetObject->GetName() == "ball" ||
                targetObject->GetName() == "banana"
            )
            {
                SetEmotion(Emotion::Happy);
            }
        }
        else
        {
            // ------------------------------------------------
            // The object has been released.
            //
            // The interaction is immediately ended:
            //
            //     - return to Idle
            //     - return to Neutral emotion
            //     - remove the target pointer
            //     - clear the reaction cooldown
            //     - reset the cooldown timer
            //
            // Setting targetObject to nullptr is important
            // because it tells the brain that there is no
            // longer an active held-object interaction.
            // ------------------------------------------------

            SetState(State::Idle);
            SetEmotion(Emotion::Neutral);

            targetObject = nullptr;

            reactionCoolDown = false;
            reactionCoolDownTimer = 0;
        }
    }


    // ========================================================
    // DETECTED OBJECT REACTION
    // ========================================================
    //
    // detectedObject is populated by Search() when the search
    // ray intersects an object's collision rectangle.
    //
    // Once an object is detected, Tingo:
    //
    //     - tracks the object with his gaze
    //     - enters Reacting
    //     - becomes Happy for recognised objects
    //     - waits for the reaction timer
    //     - speaks the appropriate reaction
    //     - clears the detected object
    //     - returns to Idle
    //
    // This creates the behaviour of Tingo finding something,
    // looking at it, and then reacting to it.
    // ========================================================

    if(detectedObject != nullptr)
    {
        // Count how long Tingo has been reacting to the
        // detected object.
        detectedTimer += dt;

        // Once the object has been detected, the rotating
        // search ray is no longer what controls Tingo's gaze.
        //
        // Instead, Tingo looks directly at the object's current
        // position.
        robot.LookAt(detectedObject->GetPosition());

        // The object has become the focus of Tingo's behaviour.
        SetState(State::Reacting);


        // ----------------------------------------------------
        // Ball and banana are recognised as objects that make
        // Tingo Happy.
        // ----------------------------------------------------

        if
        (
            detectedObject->GetName() == "ball" ||
            detectedObject->GetName() == "banana"
        )
        {
            SetEmotion(Emotion::Happy);
        }


        // ----------------------------------------------------
        // Complete the detected-object reaction after five
        // seconds.
        //
        // The five-second delay allows Tingo to remain focused
        // on the object before delivering the final reaction.
        // ----------------------------------------------------

        if(detectedTimer >= 5.0f)
        {
            // ------------------------------------------------
            // Banana-specific reaction.
            // ------------------------------------------------

            if(detectedObject->GetName() == "banana")
            {
                Speak("OI! GIMME THE BANANA");
            }


            // ------------------------------------------------
            // Ball-specific reaction.
            // ------------------------------------------------

            if(detectedObject->GetName() == "ball")
            {
                Speak("ALBY! GIMME THE BALL");
            }


            // ------------------------------------------------
            // The detected-object reaction is now complete.
            //
            // Return to Neutral, reset the reaction timer,
            // return to Idle, and clear detectedObject.
            //
            // Clearing detectedObject is especially important:
            // if the pointer remained set, the brain would
            // continue treating the same object as an active
            // detection on subsequent frames.
            // ------------------------------------------------

            SetEmotion(Emotion::Neutral);

            detectedTimer = 0.0f;

            SetState(State::Idle);

            detectedObject = nullptr;
        }
    }
}


// ============================================================
// Speak
// ============================================================
//
// Starts a new speech request.
//
// RobotBrain does not generate or play the audio itself.
// It passes the text to SpeechController.
//
// A new request is only started when SpeechController reports
// that the previous speech lifecycle has completely finished.
//
// speaking is set to true here, while Robot::SetSpeaking(true)
// is also triggered by Update() once SoundLoaded() confirms
// that the generated sound is ready.
//
// This creates an important distinction:
//
//     Speak()
//         means a speech request has been started.
//
//     SoundLoaded()
//         means generated audio is available.
//
//     SpeechFinished()
//         means the complete speech lifecycle has ended.
// ============================================================

void RobotBrain::Speak(const std::string& text)
{
    // Do not start another speech request while the previous
    // speech lifecycle is still active.
    if(speechController.SpeechFinished())
    {
        speaking = true;

        speechController.Speak(text);
    }
}


// ============================================================
// GetEmotion
// ============================================================
//
// Returns the emotion currently stored by RobotBrain.
//
// Other systems can use this value to determine which emotional
// animation or visual behaviour should be displayed.
// ============================================================

Emotion RobotBrain::GetEmotion()
{
    return emotion;
}


// ============================================================
// OnObjectPickedUp
// ============================================================
//
// Called when the object interaction system reports that an
// object has been picked up.
//
// The object address is stored in targetObject so RobotBrain
// can continue tracking that object while it is being held.
//
// RobotBrain does not create or destroy the object here.
// It simply stores a pointer to the existing Object.
//
// The object's lifetime therefore needs to remain valid while
// RobotBrain is using this pointer.
// ============================================================

void RobotBrain::OnObjectPickedUp(Object& object)
{
    // Store the address of the object currently being
    // interacted with.
    targetObject = &object;


    // ========================================================
    // BALL PICKUP
    // ========================================================
    //
    // The ball has a specific spoken reaction.
    //
    // The reaction only occurs if the cooldown is inactive.
    // Once the reaction is triggered, the cooldown is enabled
    // to prevent repeated speech from the same interaction.
    // ========================================================

    if(object.GetName() == "ball")
    {
        if(!reactionCoolDown)
        {
            Speak("Ha ha ha ha, lets play with the ball");

            reactionCoolDown = true;
        }
    }


    // ========================================================
    // BANANA PICKUP
    // ========================================================
    //
    // The banana follows the same cooldown mechanism as the
    // ball but has different speech.
    // ========================================================

    if(object.GetName() == "banana")
    {
        if(!reactionCoolDown)
        {
            Speak("Hey! A banana.");

            reactionCoolDown = true;
        }
    }
}


// ============================================================
// Search
// ============================================================
//
// Performs one frame of Tingo's search behaviour.
//
// The search is based around a continuously rotating angle.
//
// The angle is converted into a direction vector:
//
//     X = cos(angle)
//     Y = sin(angle)
//
// This produces a unit direction pointing around Tingo in a
// circle.
//
// That same direction is then used for two things:
//
//     1. Tingo's visual gaze.
//     2. The collision-detection search ray.
//
// Using the same direction for both keeps the visual search
// and the actual collision test synchronised.
//
// Search() does not itself decide how long searching lasts.
// Update() controls the overall search timer.
// ============================================================

void RobotBrain::Search(float dt)
{
    // --------------------------------------------------------
    // Advance the search angle.
    //
    // searchSpeed controls how quickly Tingo rotates the
    // search direction.
    //
    // Multiplying by dt makes the rotation time-based rather
    // than dependent on the number of frames being rendered.
    // --------------------------------------------------------

    searchAngle += searchSpeed * dt;


    // --------------------------------------------------------
    // Convert the angle into a 2D direction vector.
    //
    // cosf() provides the X component.
    // sinf() provides the Y component.
    //
    // Together they create a direction around the unit circle.
    //
    // As searchAngle increases, this vector continuously rotates.
    // --------------------------------------------------------

    Vector2 searchDirection =
    {
        cosf(searchAngle),
        sinf(searchAngle)
    };


    // --------------------------------------------------------
    // The search ray begins at Tingo's head position.
    //
    // This ensures the ray originates from the same location
    // that visually represents where Tingo is looking from.
    // --------------------------------------------------------

    searchRayOrigin = robot.GetHeadPosition();


    // --------------------------------------------------------
    // Calculate the end of the search ray.
    //
    // The direction vector is multiplied by 300 pixels to
    // create a ray extending 300 pixels from Tingo's head.
    //
    // Conceptually:
    //
    //     end = origin + direction * distance
    //
    // The result is a line from Tingo's head into the current
    // search direction.
    // --------------------------------------------------------

    searchRayEnd =
    {
        searchRayOrigin.x + searchDirection.x * 300.0f,
        searchRayOrigin.y + searchDirection.y * 300.0f
    };


    // --------------------------------------------------------
    // Make Tingo's eyes look in the same direction as the
    // search ray.
    //
    // This is important because the ray and the visual gaze
    // are driven by the same search calculation.
    //
    // Therefore, when Tingo visually looks somewhere, the
    // collision ray is looking in that same direction.
    // --------------------------------------------------------

    robot.LookAt(searchRayEnd);


    // --------------------------------------------------------
    // Test the search ray against all registered objects.
    //
    // DetectCollision() returns:
    //
    //     Object*
    //
    // if an object was hit, or:
    //
    //     nullptr
    //
    // if the ray did not intersect any registered object.
    // --------------------------------------------------------

    detectedObject = DetectCollision
    (
        searchRayOrigin,
        searchRayEnd
    );


    // ========================================================
    // OBJECT DETECTED
    // ========================================================
    //
    // Once DetectCollision() returns an object, the search has
    // found something.
    //
    // The state changes to Reacting immediately.
    //
    // The detectedObject pointer remains populated so the
    // later detected-object section of Update() can track the
    // object and manage the five-second reaction period.
    // ========================================================

    if(detectedObject != nullptr)
    {
        SetState(State::Reacting);


        // ----------------------------------------------------
        // Immediate banana detection speech.
        //
        // This happens as soon as the search ray finds the
        // banana.
        // ----------------------------------------------------

        if(detectedObject->GetName() == "banana")
        {
            Speak("I found a banana");
        }


        // ----------------------------------------------------
        // Immediate ball detection speech.
        //
        // This happens as soon as the search ray finds the
        // ball.
        // ----------------------------------------------------

        if(detectedObject->GetName() == "ball")
        {
            Speak("I found a ball");
        }
    }
}


// ============================================================
// GetSearchRayOrigin
// ============================================================
//
// Returns the current starting point of the search ray.
//
// This allows another system, such as rendering/debug code,
// to access the ray position without directly accessing the
// RobotBrain member.
// ============================================================

Vector2 RobotBrain::GetSearchRayOrigin()
{
    return searchRayOrigin;
}


// ============================================================
// GetSearchRayEnd
// ============================================================
//
// Returns the current endpoint of the search ray.
//
// Together with GetSearchRayOrigin(), this can be used by
// another system to draw or inspect the current search ray.
// ============================================================

Vector2 RobotBrain::GetSearchRayEnd()
{
    return searchRayEnd;
}


// ============================================================
// SetObjectPointers
// ============================================================
//
// Gives RobotBrain a collection of pointers to the objects
// that it is allowed to detect.
//
// RobotBrain stores the vector of pointers but does not create
// the objects and does not take ownership of them.
//
// This means the system responsible for creating the Objects
// must keep those objects alive for as long as RobotBrain
// may attempt to access them.
//
// DetectCollision() later loops through this list when the
// search ray is being tested.
// ============================================================

void RobotBrain::SetObjectPointers(std::vector<Object*> objects)
{
    this->objects = objects;
}


// ============================================================
// DetectCollision
// ============================================================
//
// Tests the supplied ray against every registered object.
//
// The function receives:
//
//     rayOrigin
//         Starting point of the search ray.
//
//     rayEnd
//         Ending point of the search ray.
//
// Each Object provides a collision rectangle.
//
// The rectangle is represented by four corners:
//
//             topLeft -------- topRight
//                |                |
//                |                |
//                |                |
//             bottomLeft ----- bottomRight
//
// The function tests whether the ray:
//
//     1. Starts inside the rectangle.
//     2. Intersects the top edge.
//     3. Intersects the right edge.
//     4. Intersects the bottom edge.
//     5. Intersects the left edge.
//
// If any test succeeds, the corresponding Object pointer is
// returned immediately.
//
// If the entire list is checked without a collision, nullptr
// is returned.
//
// This function therefore performs the actual geometric
// detection, while Search() decides when and why the ray
// should be used.
// ============================================================

Object* RobotBrain::DetectCollision(
    Vector2 rayOrigin,
    Vector2 rayEnd)
{
    // --------------------------------------------------------
    // Check every object registered with RobotBrain.
    //
    // object is a pointer because RobotBrain does not own these
    // Objects; it is simply using references to existing ones.
    // --------------------------------------------------------

    for(Object* object : objects)
    {
        // Get the rectangle used to represent this object's
        // collision area.
        Rectangle box = object->GetCollisionBox();


        // ----------------------------------------------------
        // Calculate the four corners of the collision rectangle.
        //
        // Raylib Rectangle uses:
        //
        //     x
        //     y
        //     width
        //     height
        //
        // so the opposite sides are calculated by adding width
        // and height to the starting coordinates.
        // ----------------------------------------------------

        Vector2 topLeft =
        {
            box.x,
            box.y
        };


        Vector2 topRight =
        {
            box.x + box.width,
            box.y
        };


        Vector2 bottomLeft =
        {
            box.x,
            box.y + box.height
        };


        Vector2 bottomRight =
        {
            box.x + box.width,
            box.y + box.height
        };


        // ====================================================
        // RAY / RECTANGLE COLLISION TEST
        // ====================================================
        //
        // The first test:
        //
        //     CheckCollisionPointRec(rayOrigin, box)
        //
        // handles the special case where the ray begins inside
        // the collision rectangle.
        //
        // The remaining four tests check the ray against each
        // edge of the rectangle.
        //
        // CheckCollisionLines() determines whether the search
        // ray intersects the line segment representing an edge.
        //
        // The final nullptr argument means the intersection
        // point itself is not needed here. We only need to know
        // whether a collision occurred.
        //
        // The tests cover the complete perimeter of the object:
        //
        //     top
        //     right
        //     bottom
        //     left
        //
        // If any one is true, the ray has detected this object.
        // ====================================================

        if
        (
            // The ray begins inside the object's collision box.
            CheckCollisionPointRec(rayOrigin, box) ||


            // Check the top edge.
            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                topLeft,
                topRight,
                nullptr
            ) ||


            // Check the right edge.
            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                topRight,
                bottomRight,
                nullptr
            ) ||


            // Check the bottom edge.
            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                bottomRight,
                bottomLeft,
                nullptr
            ) ||


            // Check the left edge.
            CheckCollisionLines(
                rayOrigin,
                rayEnd,
                bottomLeft,
                topLeft,
                nullptr
            )
        )
        {
            // ------------------------------------------------
            // This object's collision rectangle was hit.
            //
            // Return immediately rather than checking the
            // remaining objects.
            //
            // The caller receives the actual Object pointer,
            // allowing RobotBrain to store it in detectedObject
            // and react to that specific object.
            // ------------------------------------------------

            return object;
        }
    }


    // --------------------------------------------------------
    // No registered object's collision rectangle intersected
    // the ray.
    //
    // nullptr is used to represent "nothing detected".
    // --------------------------------------------------------

    return nullptr;
}
#include "Object.h"
#include "raylib.h"
#include <cmath>


//====================================================
// Initialise
//
// Sets up the object when it is first created.
//
// This function:
//   1. Sets the starting position.
//   2. Loads the object's image.
//   3. Works out the size of one animation frame.
//   4. Sets up the animation.
//   5. Finds the visible part of the image.
//   6. Creates a collision box around the visible part.
//
//====================================================

void Object::Initialise()
{
    // -------------------------------------------------
    // Starting position
    // -------------------------------------------------
    //
    // anchorPoint is the position we use to control
    // where the object is located in the game world.
    //
    // Starting at (0, 0) means the object begins at
    // the top-left corner of the world.
    //
    anchorPoint = Vector2(0, 0);


    // -------------------------------------------------
    // Load the object's texture
    // -------------------------------------------------
    //
    // textureFilename contains the path to the image.
    //
    // c_str() converts the C++ std::string into the
    // format that Raylib's LoadTexture() expects.
    //
    texture = LoadTexture(textureFilename.c_str());


    // -------------------------------------------------
    // Sprite sheet layout
    // -------------------------------------------------
    //
    // A sprite sheet can contain multiple frames.
    //
    // For this object we currently have:
    //
    //     1 column
    //     1 row
    //
    // So there is only one frame.
    //
    const int COLUMNS = 1;
    const int ROWS = 1;


    // -------------------------------------------------
    // Calculate the size of one frame
    // -------------------------------------------------
    //
    // The texture could contain multiple frames.
    //
    // For example, if the image was:
    //
    //     4 columns × 2 rows
    //
    // we would divide the total image width by 4
    // and the total image height by 2.
    //
    // Because we currently have 1 × 1, the frame size
    // is simply the size of the entire image.
    //
    FRAME_WIDTH = texture.width / COLUMNS;
    FRAME_HEIGHT = texture.height / ROWS;


    // Calculate how many frames exist in the sprite sheet.
    //
    // 1 column × 1 row = 1 frame.
    //
    const int TOTAL_FRAMES = COLUMNS * ROWS;


    // -------------------------------------------------
    // Animation settings
    // -------------------------------------------------
    //
    // ROTATION is the object's starting rotation.
    //
    // 0 degrees means the object starts facing normally.
    //
    const float ROTATION = 0.0f;


    // How long each animation frame should remain
    // on screen.
    //
    // This is currently irrelevant for a 1-frame
    // animation, but becomes important when we have
    // multiple frames.
    //
    const float FRAME_DURATION = 0.06f;


    // -------------------------------------------------
    // Set up the animation
    // -------------------------------------------------
    //
    // Give the Animation class all the information it
    // needs to understand the sprite sheet.
    //
    animation.Initialise
    (
        FRAME_WIDTH,       // Width of one frame
        FRAME_HEIGHT,      // Height of one frame
        TOTAL_FRAMES,      // Number of frames
        COLUMNS,           // Number of columns
        FRAME_DURATION     // Time between frames
    );


    // Set the object's starting rotation.
    rotation = ROTATION;


    // Set the object's starting scale.
    //
    // 1 means normal size.
    // 0.5 would be half size.
    // 2 would be double size.
    //
    scale = 1;


    //=================================================
    // Find the visible part of the image
    //=================================================
    //
    // PNG images often contain transparent space around
    // the actual object.
    //
    // We don't want that transparent space to be part
    // of the collision box.
    //
    // So we load the image and examine every pixel.
    //
    Image image = LoadImage(textureFilename.c_str());


    // -------------------------------------------------
    // Start with the largest possible bounds
    // -------------------------------------------------
    //
    // These four variables will eventually describe the
    // smallest rectangle that surrounds every visible
    // (non-transparent) pixel in the image.
    //
    // We are going to scan through the entire image and
    // adjust these values whenever we find a visible pixel.
    //
    //
    // LEFT and TOP
    // -------------
    //
    // We are looking for the SMALLEST x and y values.
    //
    // So we start them at the largest possible values:
    //
    //     left = image.width
    //     top  = image.height
    //
    // For example, if the image is 100 pixels wide:
    //
    //     left = 100
    //
    // and we find a visible pixel at x = 30:
    //
    //     30 < 100  ->  YES
    //
    // so left becomes:
    //
    //     left = 30
    //
    //
    // RIGHT and BOTTOM
    // ----------------
    //
    // We are looking for the LARGEST x and y values.
    //
    // So we start them at zero:
    //
    //     right  = 0
    //     bottom = 0
    //
    // As we scan through the image, these values will
    // increase whenever we find a pixel further to the
    // right or further down.
    //

    int left = image.width;
    int top = image.height;

    int right = 0;
    int bottom = 0;


    // -------------------------------------------------
    // Check every pixel in the image
    // -------------------------------------------------
    //
    // The outer loop moves down through every row.
    //
    //     y = 0
    //     y = 1
    //     y = 2
    //     y = 3
    //     ...
    //
    // The inner loop moves across each row.
    //
    //     x = 0
    //     x = 1
    //     x = 2
    //     x = 3
    //     ...
    //
    // Together, these two loops check EVERY pixel in
    // the image.
    //
    for (int y = 0; y < image.height; ++y)
    {
        for (int x = 0; x < image.width; ++x)
        {
            // -------------------------------------------------
            // Check whether this pixel is visible
            // -------------------------------------------------
            //
            // GetImageColor() gets the colour of the pixel
            // at position x, y.
            //
            // ".a" gives us the pixel's alpha value.
            //
            // Alpha controls transparency:
            //
            //     0       = completely transparent
            //     1-254   = partially transparent
            //     255     = completely opaque
            //
            // Therefore:
            //
            //     .a > 0
            //
            // means the pixel is at least partially visible.
            //
            // We only care about visible pixels because we
            // want the collision box to fit the actual object,
            // rather than the transparent padding around it.

            if (GetImageColor(image, x, y).a > 0)
            {
                // =================================================
                // Find the LEFT-most visible pixel
                // =================================================
                //
                // We want the SMALLEST X coordinate.
                //
                // For example:
                //
                //     left = 30
                //
                // If we find a visible pixel at:
                //
                //     x = 20
                //
                // then:
                //
                //     20 < 30
                //
                // so we need to change left to 20.
                //
                // The ternary statement below does this:
                //
                //     If x is smaller than left,
                //     use x.
                //     Otherwise keep left.
                //
                // -------------------------------------------------
                // Easier-to-read IF version:
                // -------------------------------------------------
                //
                // if (x < left)
                // {
                //     left = x;
                // }
                //
                // -------------------------------------------------

                left = x < left ? x : left;


                // =================================================
                // Find the TOP-most visible pixel
                // =================================================
                //
                // We want the SMALLEST Y coordinate.
                //
                // Remember:
                //
                //     y = 0  is the top of the image
                //
                // As Y increases, we move down the image.
                //
                // For example:
                //
                //     top = 20
                //
                // and we find:
                //
                //     y = 10
                //
                // Because:
                //
                //     10 < 20
                //
                // we update:
                //
                //     top = 10
                //
                // -------------------------------------------------
                // Easier-to-read IF version:
                // -------------------------------------------------
                //
                // if (y < top)
                // {
                //     top = y;
                // }
                //
                // -------------------------------------------------

                top = y < top ? y : top;


                // =================================================
                // Find the RIGHT-most visible pixel
                // =================================================
                //
                // Here we want the LARGEST X coordinate.
                //
                // Notice that we use:
                //
                //     x + 1
                //
                // instead of just x.
                //
                // A pixel at x = 20 occupies the space:
                //
                //     20 → 21
                //
                // So its RIGHT EDGE is at 21.
                //
                // This is important because later we calculate:
                //
                //     width = right - left
                //
                // For example:
                //
                //     left  = 10
                //     right = 15
                //
                //     width = 15 - 10
                //           = 5 pixels
                //
                // -------------------------------------------------
                // Easier-to-read IF version:
                // -------------------------------------------------
                //
                // if (x + 1 > right)
                // {
                //     right = x + 1;
                // }
                //
                // -------------------------------------------------

                right = x + 1 > right ? x + 1 : right;


                // =================================================
                // Find the BOTTOM-most visible pixel
                // =================================================
                //
                // We want the LARGEST Y coordinate.
                //
                // Just like "right", we use y + 1 because
                // we are recording the EDGE AFTER the pixel.
                //
                // For example:
                //
                //     bottom pixel = y 50
                //
                // That pixel occupies:
                //
                //     50 → 51
                //
                // Therefore:
                //
                //     bottom = 51
                //
                // -------------------------------------------------
                // Easier-to-read IF version:
                // -------------------------------------------------
                //
                // if (y + 1 > bottom)
                // {
                //     bottom = y + 1;
                // }
                //
                // -------------------------------------------------

                bottom = y + 1 > bottom ? y + 1 : bottom;
            }
        }
    }

    // -------------------------------------------------
    // We no longer need the CPU-side image.
    // -------------------------------------------------
    //
    // The texture is still loaded for drawing.
    //
    // This Image was only needed temporarily so we
    // could inspect its pixels.
    //
    UnloadImage(image);


    //=================================================
    // Calculate the visible object's size
    //=================================================
    //
    // Example:
    //
    // left   = 20
    // right  = 220
    //
    // visible width = 220 - 20 = 200 pixels
    //
    const float visibleWidth =
        static_cast<float>(right - left);


    // Same idea for height.
    //
    const float visibleHeight =
        static_cast<float>(bottom - top);


    //=================================================
    // Calculate the visible object's offset
    //=================================================
    //
    // The sprite's anchor is in the CENTRE of the
    // entire animation frame.
    //
    // But the visible object might not be centred
    // inside that frame.
    //
    // collisionOffset tells us how far the visible
    // object's top-left corner is from the centre
    // of the sprite frame.
    //
    collisionOffset =
    {
        (left - FRAME_WIDTH / 2.0f) * scale,

        (top - FRAME_HEIGHT / 2.0f) * scale
    };


    //=================================================
    // Set the drawing anchor
    //=================================================
    //
    // DrawTexturePro uses the origin/anchor point when
    // positioning, rotating and scaling the sprite.
    //
    // We want that point to be the centre of the
    // animation frame.
    //
    // Therefore:
    //
    //     half the frame width
    //     half the frame height
    //
    anchorOffset =
    {
        FRAME_WIDTH / 2.0f,
        FRAME_HEIGHT / 2.0f
    };


    //=================================================
    // Create the collision rectangle
    //=================================================
    //
    // The collision box starts at:
    //
    //     anchor position
    //          +
    //     visible image offset
    //
    // This means the collision box lines up with the
    // actual visible pixels rather than the transparent
    // padding around the image.
    //
    collisionBox = Rectangle
    (
        anchorPoint.x + collisionOffset.x,
        anchorPoint.y + collisionOffset.y,

        // Width of the visible part.
        visibleWidth * scale,

        // Height of the visible part.
        visibleHeight * scale
    );
}



//====================================================
// SetTextureFilename
//
// Stores the filename/path of the image that this
// object will use.
//
// The actual texture is loaded later by Initialise().
//
//====================================================

void Object::SetTextureFilename(std::string textureFileName)
{
    // "this->textureFilename" means:
    //
    //     the textureFilename belonging to THIS object.
    //
    // We are copying the function parameter
    // "textureFileName" into it.
    //
    this->textureFilename = textureFileName;
}



//====================================================
// UpdateObject
//
// Called every frame to update the object.
//
// This handles:
//   - animation
//   - mouse clicking
//   - dragging
//   - collision box movement
//
//====================================================

void Object::UpdateObject(
    float dt,
    Vector2 mousePosition,
    bool mousePressed
)
{
    // -------------------------------------------------
    // Update animation
    // -------------------------------------------------
    //
    // Pass the elapsed time to the Sprite class.
    //
    // "dt" is normally the amount of time that has
    // passed since the previous frame.
    //
    Sprite::Update(dt);


    //=================================================
    // Check whether the mouse clicked the object
    //=================================================
    //
    // CheckCollisionPointRec asks:
    //
    // "Is the mouse position inside the collision
    // rectangle?"
    //
    // We ALSO check mousePressed.
    //
    // Both must be true.
    //
    if (
        CheckCollisionPointRec(mousePosition, collisionBox)
        && mousePressed
    )
    {
        // Toggle the dragging state.
        //
        // If it was false:
        //
        //     false -> true
        //
        // If it was true:
        //
        //     true -> false
        //
        heldByMouse = !heldByMouse;


        // -------------------------------------------------
        // Remember where inside the object we clicked.
        // -------------------------------------------------
        //
        // Without this, the object would jump so that its
        // centre was directly underneath the mouse.
        //
        // mouseGrabOffset remembers the difference between
        // the mouse position and the object's anchor point.
        //
        mouseGrabOffset =
        {
            mousePosition.x - anchorPoint.x,
            mousePosition.y - anchorPoint.y
        };
    }


    //=================================================
    // Move the object while it is being dragged
    //=================================================
    //
    if (heldByMouse)
    {
        // Move the anchor point to follow the mouse.
        //
        // We subtract mouseGrabOffset so that the object
        // stays grabbed at the same point where the user
        // originally clicked it.
        //
        anchorPoint =
        {
            mousePosition.x - mouseGrabOffset.x,
            mousePosition.y - mouseGrabOffset.y
        };
    }


    //=================================================
    // Move the collision box
    //=================================================
    //
    // The collision box belongs to the object, so when
    // the anchor moves, the collision box must move too.
    //
    // We add collisionOffset because the visible image
    // may not be centred inside the sprite frame.
    //
    collisionBox.x =
        anchorPoint.x + collisionOffset.x;

    collisionBox.y =
        anchorPoint.y + collisionOffset.y;
}



//====================================================
// IsHeldByMouse
//
// Returns whether the object is currently being
// dragged by the mouse.
//
// Returns:
//     true  = object is being held
//     false = object is not being held
//
//====================================================

bool Object::IsHeldByMouse() const
{
    return heldByMouse;
}



//====================================================
// DrawCollisionBox
//
// Draws the collision rectangle around the object.
//
// This is mainly a DEBUGGING tool so we can see
// exactly where Raylib thinks the collision area is.
//
//====================================================

void Object::DrawCollisionBox()
{
    DrawRectangleLines
    (
        collisionBox.x,
        collisionBox.y,
        collisionBox.width,
        collisionBox.height,
        RED
    );
}



//====================================================
// GetCollisionBox
//
// Returns the object's current collision rectangle.
//
// Other parts of the program can use this to check
// collisions with this object.
//
//====================================================

Rectangle Object::GetCollisionBox()
{
    return collisionBox;
}



//====================================================
// SetName
//
// Gives the object a name.
//
// This can be useful for identifying different objects,
// for example:
//
//     "Ball"
//     "Book"
//     "Guitar"
//     "Toy"
//====================================================

void Object::SetName(std::string name)
{
    objectName = name;
}



//====================================================
// GetName
//
// Returns the object's current name.
//====================================================

std::string Object::GetName()
{
    return objectName;
}
//====================================================
// Game.cpp
//
// Controls the main game loop.
//
// The Game class is responsible for initialising the
// application, processing input, updating the game
// state, drawing each frame and shutting everything
// down when the program exits.
//====================================================

// Main game loop.
//
// Initialise()
//       │
//       ▼
// ┌─────────────────────┐
// │ HandleInput()       │
// │ Update()            │
// │ BeginDrawing()      │
// │ Draw()              │
// │ EndDrawing()        │
// └─────────────────────┘
//          ▲
//          │
// WindowShouldClose()
//          │
// Shutdown()

#include "raylib.h"

#include "Game.h"
#include "Constants.h"

#include "Speech.h"

// Initialise the game and load required resources.
void Game::Initialise()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

	InitAudioDevice();

	robot.Initialise();

	SetTargetFPS(TARGET_FPS);

	background = LoadTexture("assets/images/background/space.jpg");
}

// Process keyboard input.
void Game::HandleInput()
{
	if (input.LeftPressed())
	{
		robot.RotateHeadLeft();
	}
	else if (input.RightPressed())
	{
		robot.RotateHeadRight();
	}
	else
	{
		robot.ReturnHeadToCentre();
	}
}

// Update the game state.
void Game::Update(const float dt)
{
	// Make the robot follow the mouse with its eyes.
	robot.LookAt(input.MousePosition());

	// Update the robot and its animations.
	robot.Update(dt);

	// Temporary speech test.
	if (IsKeyPressed(KEY_SPACE))
	{
		Speech::Speak("Hello there. My name is Tingo Bingo. whats your name?");

		Sound speech = LoadSound("assets/audio/voice/speech.wav");

		SetSoundPitch(speech, 0.82f);
		SetSoundVolume(speech, 0.85f);

		// TODO: Apply voice effects here.
		// bitcrusher(jsdhkjs)

		PlaySound(speech);

		//UnloadSound(speech);
	}

	// Temporary speech test.
	if (IsKeyPressed(KEY_T))
	{
		Speech::Speak("Hello Alby. Nice to meet you. We are going to have lots of fun");

		Sound speech = LoadSound("assets/audio/voice/speech.wav");

		SetSoundPitch(speech, 0.82f);
		SetSoundVolume(speech, 0.85f);

		// TODO: Apply voice effects here.
		// bitcrusher(jsdhkjs)

		PlaySound(speech);

		//UnloadSound(speech);
	}

	// Temporary speech test.
	if (IsKeyPressed(KEY_P))
	{
		Speech::Speak("Hello Alby. Virtual tingo bingo has a problem. Can you help?");

		Sound speech = LoadSound("assets/audio/voice/speech.wav");

		SetSoundPitch(speech, 0.82f);
		SetSoundVolume(speech, 0.85f);

		// TODO: Apply voice effects here.
		// bitcrusher(jsdhkjs)

		PlaySound(speech);

		//UnloadSound(speech);
	}
}

// Draw the current frame.
void Game::Draw()
{
	ClearBackground(BLACK);

	DrawTexture(background, 0, 0, WHITE);

	robot.Draw();
}

// Release resources before exiting.
void Game::Shutdown()
{
	robot.Shutdown();

	UnloadTexture(background);

	CloseAudioDevice();

	CloseWindow();
}

// Run the main game loop.
void Game::Run()
{
	float dt = GetFrameTime();

	Initialise();

	while (!WindowShouldClose())
	{
		HandleInput();

		dt = GetFrameTime();
		Update(dt);

		BeginDrawing();

		Draw();

		EndDrawing();
	}

	Shutdown();
}
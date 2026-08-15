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
#include "Emotion.h"


// Initialise the game and load required resources.
void Game::Initialise()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

	InitAudioDevice();

	robot.Initialise();

	ball.Initialise();

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

	if (input.SpacePressed())
	{
		robot.Speak("Hello Alby, my name is tingo bingo");
	}

	if(input.H_Pressed())
	{
		robot.SetEmotion(Emotion::Happy);
	}
}

// Update the game state.
void Game::Update(const float dt)
{
	robot.LookAt(ball.GetPosition());

	robot.Update(dt);
	
	ball.UpdateToy(dt, input.MousePosition(), input.LeftMouseButtonPressed());

	if(ball.IsDragging())
	{
		robot.SetEmotion(Emotion::Happy);
	}
	else{
		robot.SetEmotion(Emotion::Neutral);
	}
}

// Draw the current frame.
void Game::Draw()
{
	ClearBackground(BLACK);

	DrawTexture(background, 0, 0, WHITE);

	robot.Draw();
	ball.Draw();
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
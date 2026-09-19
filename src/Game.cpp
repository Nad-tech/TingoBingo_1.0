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
#include "MyTransform.h"

bool drawGrid = false;

void DrawDebugGrid()
{
    const int gridSize = 100;

    const int originX = SCREEN_WIDTH / 2;
    const int originY = SCREEN_HEIGHT / 2;

    // Vertical grid lines
    for (int x = originX; x <= SCREEN_WIDTH; x += gridSize)
        DrawLine(x, 0, x, SCREEN_HEIGHT, LIGHTGRAY);

    for (int x = originX - gridSize; x >= 0; x -= gridSize)
        DrawLine(x, 0, x, SCREEN_HEIGHT, LIGHTGRAY);

    // Horizontal grid lines
    for (int y = originY; y <= SCREEN_HEIGHT; y += gridSize)
        DrawLine(0, y, SCREEN_WIDTH, y, LIGHTGRAY);

    for (int y = originY - gridSize; y >= 0; y -= gridSize)
        DrawLine(0, y, SCREEN_WIDTH, y, LIGHTGRAY);

    // Cartesian axes
    DrawLine(0, originY, SCREEN_WIDTH, originY, DARKGRAY);
    DrawLine(originX, 0, originX, SCREEN_HEIGHT, DARKGRAY);
}

// Initialise the game and load required resources.
void Game::Initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    // Initialise robot
	robotWorldPos = {0, 0};
    robot.Initialise();
	MyTransform initialTransform
	{
		.position = robotWorldPos,
		.pivot = {0, 0},
		.rotation = 0.0f,
		.scale = SCALE
	};
	robot.SetTransform(initialTransform);

    // Initialise ball
    //ball.SetTextureFilename("./assets/images/toys/ball.png");
    //ball.Initialise();
	//ball.SetAnchorPoint({100, 100});
    //ball.SetName("ball");

    // Initialise banana
    //banana.SetTextureFilename("./assets/images/toys/banana.png");
    //banana.Initialise();
	//banana.SetAnchorPoint({300, 300});
    //banana.SetName("banana");

    //objects = {&ball, &banana};

    //robot.SetObjectPointers(objects);

    SetTargetFPS(TARGET_FPS);

    background = LoadTexture(
        "assets/images/background/space.jpg"
    );
}

// Process keyboard input.
void Game::HandleInput()
{
	if (input.SpacePressed())
	{
		robot.Speak("Hello Alby, my name is tingo bingo");
	}

	if(input.H_Pressed())
	{
		robot.SetEmotion(Emotion::Happy);
	}

	if(input.RightPressed()){

	}

	if(input.G_Pressed())
	{
		drawGrid = !drawGrid;
	}
}

// Update the game state.
void Game::Update(const float dt)
{
	ball.UpdateObject(
			dt, input.MousePosition(),
			input.LeftMouseButtonPressed()
		);

	banana.UpdateObject(
			dt, input.MousePosition(), 
			input.LeftMouseButtonPressed()
		);

	if(banana.IsHeldByMouse())
	{
		robot.OnObjectPickedUp(banana);
	}
	
	if(ball.IsHeldByMouse())
	{
		robot.OnObjectPickedUp(ball);
	}
	
	robot.Update(dt);
}

// Draw the current frame.
void Game::Draw()
{
	ClearBackground(BLACK);

	DrawTexture(background, 0, 0, WHITE);

	robot.Draw();
	
	//ball.DrawCollisionBox();
	ball.Draw();
	
	//banana.DrawCollisionBox();
	banana.Draw();
	
	//DrawLineEx(robot.GetSearchRayOrigin(), robot.GetSearchRayEnd(), 2.0f, RED);

	if(drawGrid) {
		DrawDebugGrid();
	}
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
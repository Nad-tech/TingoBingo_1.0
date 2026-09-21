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
    
	MyTransform initialTransform
	{
		.position = robotWorldPos,
		.pivot = {0, 0},
		.rotation = 0.0f,
		.scale = SCALE
	};
	robot.SetTransform(initialTransform);
	robot.Initialise();

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
	if (IsKeyPressed(KEY_F3))
	{
		drawDebugOverlay = !drawDebugOverlay;
	}

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
	//ball.Draw();
	
	//banana.DrawCollisionBox();
	//banana.Draw();
	
	//DrawLineEx(robot.GetSearchRayOrigin(), robot.GetSearchRayEnd(), 2.0f, RED);

	if(drawGrid) {
		DrawDebugGrid();
	}

	if (drawDebugOverlay)
	{
		DrawDebugOverlay();
	}
}

void Game::DrawDebugOverlay() const
{
	MyTransform robotTransform = robot.GetTransform();

	Vector2 robotScreenPosition =
	{
		SCREEN_WIDTH / 2.0f + robotTransform.position.x * robotTransform.scale,
		SCREEN_HEIGHT / 2.0f - robotTransform.position.y * robotTransform.scale
	};

	Vector2 pivotScreenPosition =
	{
		robotScreenPosition.x + robotTransform.pivot.x * robotTransform.scale,
		robotScreenPosition.y - robotTransform.pivot.y * robotTransform.scale
	};

	Vector2 searchOrigin = robot.GetSearchRayOrigin();
	Vector2 searchEnd = robot.GetSearchRayEnd();

	DrawLineEx(searchOrigin, searchEnd, 2.0f, YELLOW);
	DrawCircleV(searchOrigin, 6.0f, ORANGE);
	DrawCircleV(searchEnd, 6.0f, RED);

	DrawCircleV(robotScreenPosition, 7.0f, GREEN);
	DrawCircleV(pivotScreenPosition, 5.0f, MAGENTA);
	DrawLineEx(
		robotScreenPosition,
		{
			robotScreenPosition.x + cosf(robotTransform.rotation * DEG2RAD) * 40.0f,
			robotScreenPosition.y - sinf(robotTransform.rotation * DEG2RAD) * 40.0f
		},
		2.0f,
		BLUE
	);

	DrawRectangle(8, 8, 285, 92, Fade(BLACK, 0.75f));
	DrawText("F3 Debug Overlay", 18, 16, 18, WHITE);
	DrawText("Green: robot position", 18, 39, 14, GREEN);
	DrawText("Magenta: transform pivot", 18, 57, 14, MAGENTA);
	DrawText("Yellow: search ray", 18, 75, 14, YELLOW);
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
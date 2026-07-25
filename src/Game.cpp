#include "raylib.h"

#include "Game.h"
#include "Constants.h"


void  Game::Initialise()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	
	robot.Initialise();

	SetTargetFPS(TARGET_FPS);

	background = LoadTexture("assets/images/background/space.jpg");
}

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

void Game::Update(const float dt)
{	
	robot.LookAt(input.MousePosition());
	robot.Update(dt);
}

void Game::Draw()
{
	ClearBackground(BLACK);
	
	DrawTexture(background, 0, 0, WHITE);

	robot.Draw();
}

void Game::Shutdown()
{
	robot.Shutdown();

	UnloadTexture(background);

	CloseWindow();
}

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
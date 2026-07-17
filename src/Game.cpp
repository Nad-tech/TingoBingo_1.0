#include "raylib.h"

#include "Game.h"
#include "Constants.h"


void  Game::Initialise()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	
	robot.Initialise();
	object.Initialise();

	SetTargetFPS(TARGET_FPS);
}

void Game::HandleInput(){}

void Game::Update(const float dt)
{	
	robot.Update(dt);
	object.Update(dt);
}

void Game::Draw()
{
	ClearBackground(BLACK);
	
	robot.Draw();
	object.Draw();
}

void Game::Shutdown()
{
	robot.Shutdown();
	object.Shutdown();

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
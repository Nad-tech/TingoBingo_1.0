#include "raylib.h"

#include "Game.h"
#include "Constants.h"


void  Game::Initialise()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
	
	SetTargetFPS(TARGET_FPS);
}

void Game::HandleInput(){}

void Game::Update(const float dt)
{	
	agent.Update(dt);
	object.Update(dt);
}

void Game::Draw()
{
	ClearBackground(RAYWHITE);

	DrawText(WINDOW_TITLE, 20, 20, 30, BLACK);
	
	agent.Draw();
	object.Draw();
}

void Game::Shutdown()
{
	CloseWindow();
}

void Game::Run()
{
	float dt = GetFrameTime();
	
	Initialise();
	
	while (!WindowShouldClose()) 
	{
		HandleInput();
		Update(dt);
		
		BeginDrawing();
		
		Draw();
		
		EndDrawing();
	}
	
	Shutdown();
}
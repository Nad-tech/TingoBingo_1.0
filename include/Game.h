#pragma once

#include "Robot.h"
#include "Input.h"
#include "Object.h"
#include "BodyDimensions.h"
class Game
{
public:
	void Run();
	
private:
	void Initialise();
	void Shutdown();

	void HandleInput();
	void Update(const float dt);
	void Draw();
	void DrawDebugOverlay() const;
	
	Robot robot;
	Vector2 robotWorldPos;
	Input input;
	Object ball;
	Object banana;
	Texture2D background;
	std::vector<Object*> objects; 
	bool drawDebugOverlay = false;
};
#pragma once

#include "Robot.h"
#include "Input.h"
#include "Toy.h"
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
	
	Robot robot;
	Input input;
	Toy ball;
	Toy banana;
	Texture2D background;
	std::vector<Toy*> toys; 
};
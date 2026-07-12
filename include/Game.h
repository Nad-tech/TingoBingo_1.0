#pragma once

#include "Agent.h"
#include "Object.h"

class Game
{
public:
	
	void Run();
	
private:
	
	void Initialise();
	void HandleInput();
	void Update(const float dt);
	void Draw();
	void Shutdown();
	
	Agent agent;
	Object object;
};
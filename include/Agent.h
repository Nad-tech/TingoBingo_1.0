#pragma once

#include "raylib.h"

class Agent 
{
public:
	
	Agent();
	
	void Update(float dt);
	void Draw() const;
	
private:
	
	Vector2 position;	
};
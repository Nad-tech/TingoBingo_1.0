#pragma once

#include "raylib.h"

class Agent 
{
public:
	
	Agent();
	
	void Update(float dt);
	void Draw() const;
	void LoadResources();
	void UnloadResources();

	
private:
	
	Texture2D headTexture;
	Texture2D headTextureBlank;
	Vector2 position;
};
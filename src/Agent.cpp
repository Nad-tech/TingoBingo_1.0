#include "Agent.h"
#include "raylib.h"
#include "Constants.h"

//BADBADBAD
float tingoHeadScale = 0.5f;

Agent::Agent()
{
	position = {0,0};

	//varialbles
}

void Agent::Update(float dt)
{
    
}

void Agent::Draw() const
{
	DrawTextureEx(
        headTextureBlank,
        position,
        0.0f,
        tingoHeadScale,
        WHITE
    );
}

void Agent::LoadResources()
{
    headTextureBlank = LoadTexture("../assets/images/TingoHeadBlank.png");

    if (!IsTextureValid(headTexture))
    {
        TraceLog(LOG_ERROR, "Failed to load TingoHeadBlank.png");
    }

    TraceLog(LOG_INFO, "TingoHeadBlank.png: Texture size: %d x %d",
             headTexture.width,
             headTexture.height);

    position = {
        (SCREEN_WIDTH - headTextureBlank.width * tingoHeadScale) / 2 , 
        (SCREEN_HEIGHT - headTextureBlank. height * tingoHeadScale) / 2
    };
}

void Agent::UnloadResources()
{
    UnloadTexture(headTextureBlank);
}

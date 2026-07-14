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
    position.x -= 100 * dt;

    if (position.x + headTexture.width * tingoHeadScale <= 0) 
    {
        position.x = SCREEN_WIDTH;
    }
}

void Agent::Draw() const
{
	DrawTextureEx(
        headTexture,
        position,
        0.0f,
        tingoHeadScale,
        WHITE
    );
}

void Agent::LoadResources()
{
    headTexture = LoadTexture("../assets/images/TingoHead.png");

    if (!IsTextureValid(headTexture))
    {
        TraceLog(LOG_ERROR, "Failed to load TingoHead.png");
    }

    TraceLog(LOG_INFO, "TingoHead.png: Texture size: %d x %d",
             headTexture.width,
             headTexture.height);

    position = {
        (SCREEN_WIDTH - headTexture.width * tingoHeadScale) / 2 , 
        (SCREEN_HEIGHT - headTexture. height * tingoHeadScale) / 2
    };
}

void Agent::UnloadResources()
{
    UnloadTexture(headTexture);
}

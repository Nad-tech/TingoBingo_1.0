#include "Agent.h"

Agent::Agent()
{
	position = {600, 350};

	//varialbles
}

void Agent::Update(float dt)
{
    position.x -= 100 * dt;
}

void Agent::Draw() const
{
	DrawRectangle(
        position.x - 35,
        position.y + 30,
        70,
        70,
        GRAY
    );
}
	
#include "Body/Neck.h"

void Neck::Initialise(){}
void Neck::Update(float dt, bool speaking, Emotion emotion){}
void Neck::Draw() const{}
void Neck::SetRotation(float rotation){}
void Neck::SetBodyDimensions(float bW, float bH){}
void Neck::SetAnchorPoint(Vector2 anchorPoint){}
Head& Neck::GetHead()
{
    return head;
}
void Neck::Shutdown(){}
#pragma once

#include "raylib.h"
#include "Constants.h"
#include "MyTransform.h"
#include "BodyDimensions.h"

class Shape
{
protected:
    MyTransform transform;
    float width = 0.0f;
    float height = 0.0f;
    Color color;

public:
    explicit Shape(Color color = CARDBOARD_DARK) : color(color) {}
    virtual void Initialise() = 0;
    void Shutdown();
    
    virtual void Draw() const;
    
    void SetDimensions(float width, float height);
    void SetTransform(MyTransform transform);

    virtual ~Shape() = default;
};
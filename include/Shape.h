#pragma once

#include "raylib.h"
#include "Constants.h"
#include "MyTransform.h"
#include "BodyDimensions.h"

class Shape
{
protected:
    BodyDimensions& dimensions;
    MyTransform transform;

public:
    Shape(BodyDimensions& dimensions);
    virtual void Initialise() = 0;
    void Shutdown();
    
    virtual void Draw() const;
    
    void SetTransform(MyTransform transform);

    virtual ~Shape() = default;
};
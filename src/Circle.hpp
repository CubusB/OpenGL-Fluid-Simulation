#pragma once

#include "BasicInclude.hpp"
#include "math/Vectors.hpp"

class Circle
{
public:
    float x, y, radius;
    Vector3D color;
    Circle(float x, float y, float radius, Vector3D color = Vector3D(1, 1, 1))
        : x(x), y(y), radius(radius), color(color)
    {
    }
};
#pragma once

class Vector3D
{
public:
    float x, y, z;
    Vector3D(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z)
    {
    }

    Vector3D& operator*(float value){
        this->x *= value;
        this->y *= value;
        this->z *= value;
        return *this;
    }
};
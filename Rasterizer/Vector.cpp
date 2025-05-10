// src/Vector.cpp
#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0) {}
Vector::Vector(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
Vector Vector::operator+(const Vector& o) const { return { x + o.x, y + o.y, z + o.z }; }
Vector Vector::operator-(const Vector& o) const { return { x - o.x, y - o.y, z - o.z }; }
Vector Vector::operator*(float s)      const { return { x * s,   y * s,   z * s }; }

// dot product
float Vector::dot(const Vector& o) const {
    return x * o.x + y * o.y + z * o.z;
}
// cross product
Vector Vector::cross(const Vector& o) const {
    return {
        y * o.z - z * o.y,
        z * o.x - x * o.z,
        x * o.y - y * o.x
    };
}

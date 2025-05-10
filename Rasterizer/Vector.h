#pragma once

struct Vector {
    float x, y, z;
    Vector();
    Vector(float x_, float y_, float z_);
    Vector operator+(const Vector& o) const;
    Vector operator-(const Vector& o) const;
    Vector operator*(float s)      const;

    // new:
    float   dot  (const Vector& o) const;
    Vector  cross(const Vector& o) const;
};
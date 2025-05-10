#pragma once

#include <vector>
#include "Vector.h"
#include "Triangle.h"
#include "Color.h"

class Model {
public:
    std::vector<Vector>    vertices;
    std::vector<Triangle>  triangles;
    Model(const std::vector<Color>& face_colors);
};


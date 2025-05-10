#pragma once

#include "Model.h"
#include "Vector.h"

struct Instance {
    const Model* model;
    Vector       position;
    float        ax, ay, az;
};
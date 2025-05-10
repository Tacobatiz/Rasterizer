#pragma once

#include <vector>
#include "Color.h"
#include "Instance.h"

class Rasterizer {
public:
    Rasterizer(int width, int height, float focal);
    void clear(const Color& bg);
    void draw(const std::vector<Instance>& scene);
    void writePPM(const char* filename) const;

private:
    int               W, H;
    float             d;
    std::vector<Color>framebuffer;
    std::vector<float>depth;
};

#include <cmath>
#include "Constant.h"
#include <vector>
#include "Rasterizer.h"
#include "Model.h"
#include "Instance.h"

int main() {
    Rasterizer rz(500, 500, 1.0f);
    rz.clear({ 255,255,255 });

    std::vector<Color> face_colors = {
      {255,   0,   0},
      {  0,   0, 255},
      {255, 255,   0},
      {  0, 255,   0},
      {255,   0, 255},
      {  0, 255, 255}
    };

    Model cube(face_colors);

    Model scaledCube = cube;
    for (auto& vertex : scaledCube.vertices) {
        vertex.x *= 1.5f;
        vertex.y *= 1.5f;
        vertex.z *= 1.5f;
    }

    std::vector<Instance> scene = {
        {&cube, {-1.5f, -1.0f, 7.0f}, -PI / 6, PI / 4, 0},
        {&cube, {1.25f, 1.0f, 7.5f}, -PI / 6, PI / 4 + PI, 0},
        {&scaledCube, {2.0f, -2.0f, 6.0f}, PI / 8, -PI / 5, 0}
    };

    rz.draw(scene);
    rz.writePPM("output.ppm");
    return 0;
}

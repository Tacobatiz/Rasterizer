#include "Model.h"

Model::Model(const std::vector<Color>& face_colors) {
    vertices = {
        { 1,  1,  1},{-1,  1,  1},{-1, -1,  1},{ 1, -1,  1},
        { 1,  1, -1},{-1,  1, -1},{-1, -1, -1},{ 1, -1, -1}
    };
    const int face_tris[6][2][3] = {
        {{0,1,2},{0,2,3}}, {{4,7,6},{4,6,5}},
        {{1,5,6},{1,6,2}}, {{4,0,3},{4,3,7}},
        {{4,5,1},{4,1,0}}, {{3,2,6},{3,6,7}}
    };
    for (int f = 0; f < 6; ++f) {
        for (int t = 0; t < 2; ++t) {
            triangles.push_back({
                face_tris[f][t][0],
                face_tris[f][t][1],
                face_tris[f][t][2],
                face_colors[f]
                });
        }
    }
}

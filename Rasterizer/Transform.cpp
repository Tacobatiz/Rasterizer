#include "Transform.h"
#include <cmath>

std::vector<float> interpolate(int i0, float d0, int i1, float d1) {
    if (i0 == i1) return { d0 };
    std::vector<float> vals(i1 - i0 + 1);
    float a = (d1 - d0) / (i1 - i0);
    for (int i = 0; i < (int)vals.size(); ++i)
        vals[i] = d0 + a * i;
    return vals;
}

Vector rotate(const Vector& v, float ax, float ay, float az) {
    float cx = std::cos(ax), sx = std::sin(ax);
    float y = v.y * cx - v.z * sx;
    float z = v.y * sx + v.z * cx;
    float x = v.x;

    float cy = std::cos(ay), sy = std::sin(ay);
    float x2 = x * cy + z * sy;
    float z2 = -x * sy + z * cy;

    float cz = std::cos(az), sz = std::sin(az);
    return {
        x2 * cz - y * sz,
        x2 * sz + y * cz,
        z2
    };
}

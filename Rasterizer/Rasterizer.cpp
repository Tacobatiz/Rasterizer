#include "Rasterizer.h"
#include "Transform.h"
#include <limits>
#include <fstream>
#include <algorithm>
#include <iostream>

Rasterizer::Rasterizer(int width, int height, float focal)
    : W(width), H(height), d(focal),
    framebuffer(W* H), depth(W* H)
{}

void Rasterizer::clear(const Color& bg) {
    std::fill(framebuffer.begin(), framebuffer.end(), bg);
    std::fill(depth.begin(), depth.end(), std::numeric_limits<float>::infinity());
}

void Rasterizer::draw(const std::vector<Instance>& scene) {
    for (const auto& inst : scene) {
        std::vector<Vector> camVerts;
        camVerts.reserve(inst.model->vertices.size());
        for (const auto& v : inst.model->vertices) {
            camVerts.push_back(rotate(v, inst.ax, inst.ay, inst.az)
                + inst.position);
        }

        std::vector<Vector> projVerts;
        std::vector<float>  projZ;
        projVerts.reserve(camVerts.size());
        projZ.reserve(camVerts.size());
        for (const auto& cv : camVerts) {
            float z = cv.z;
            projZ.push_back(z);
            float x = cv.x * d / z;
            float y = cv.y * d / z;
            int px = int((x + 1) * 0.5f * W);
            int py = int((1 - (y + 1) * 0.5f) * H);
            projVerts.push_back({ float(px), float(py), z });
        }

        for (const auto& tri : inst.model->triangles) {
            const Vector& v0 = camVerts[tri.i0],
                & v1 = camVerts[tri.i1],
                & v2 = camVerts[tri.i2];
            Vector e1 = v1 - v0;
            Vector e2 = v2 - v0;
            Vector normal = e1.cross(e2);

            if (normal.z >= 0)
                continue;

            struct VZ { Vector v; float z; };
            VZ arr[3] = {
                { projVerts[tri.i0], projZ[tri.i0] },
                { projVerts[tri.i1], projZ[tri.i1] },
                { projVerts[tri.i2], projZ[tri.i2] }
            };
            std::sort(arr, arr + 3, [](auto& a, auto& b) { return a.v.y < b.v.y; });

            int y0 = int(arr[0].v.y),
                y1 = int(arr[1].v.y),
                y2 = int(arr[2].v.y);

            if (y0 == y2)
                continue;

            auto x01 = interpolate(y0, arr[0].v.x, y1, arr[1].v.x);
            auto z01 = interpolate(y0, arr[0].z, y1, arr[1].z);
            auto x12 = interpolate(y1, arr[1].v.x, y2, arr[2].v.x);
            auto z12 = interpolate(y1, arr[1].z, y2, arr[2].z);
            auto x02 = interpolate(y0, arr[0].v.x, y2, arr[2].v.x);
            auto z02 = interpolate(y0, arr[0].z, y2, arr[2].z);

            std::vector<float> x_left, x_right, z_left, z_right;

            int m = static_cast<int>(x01.size());
            for (int i = 0; i < m; i++) {
                if (x01[i] < x02[i]) {
                    x_left.push_back(x01[i]);
                    z_left.push_back(z01[i]);
                    x_right.push_back(x02[i]);
                    z_right.push_back(z02[i]);
                }
                else {
                    x_left.push_back(x02[i]);
                    z_left.push_back(z02[i]);
                    x_right.push_back(x01[i]);
                    z_right.push_back(z01[i]);
                }
            }

            if (y1 < y2) {
                int n = static_cast<int>(x12.size());
                for (int i = 0; i < n; i++) {
                    int idx = i + (y1 - y0);
                    if (idx >= static_cast<int>(x02.size())) continue; 

                    if (x12[i] < x02[idx]) {
                        x_left.push_back(x12[i]);
                        z_left.push_back(z12[i]);
                        x_right.push_back(x02[idx]);
                        z_right.push_back(z02[idx]);
                    }
                    else {
                        x_left.push_back(x02[idx]);
                        z_left.push_back(z02[idx]);
                        x_right.push_back(x12[i]);
                        z_right.push_back(z12[i]);
                    }
                }
            }

            for (int yi = y0; yi <= y2; ++yi) {
                if (yi < 0 || yi >= H) continue; 

                int idx = yi - y0;
                if (idx < 0 || idx >= static_cast<int>(x_left.size())) continue; 

                float xl = x_left[idx];
                float xr = x_right[idx];
                float zl = z_left[idx];
                float zr = z_right[idx];

                int xi0 = std::max(0, std::min(W - 1, int(std::floor(xl))));
                int xi1 = std::max(0, std::min(W - 1, int(std::ceil(xr))));

                if (xi0 > xi1) continue;

                auto zSpan = interpolate(xi0, zl, xi1, zr);

                for (int xi = xi0; xi <= xi1; ++xi) {
                    int pix = yi * W + xi;
                    if (pix < 0 || pix >= static_cast<int>(depth.size())) continue;

                    int z_idx = xi - xi0;
                    if (z_idx < 0 || z_idx >= static_cast<int>(zSpan.size())) continue;

                    if (zSpan[z_idx] < depth[pix]) {
                        framebuffer[pix] = tri.color;
                        depth[pix] = zSpan[z_idx];
                    }
                }
            }
        }
    }
}

void Rasterizer::writePPM(const char* filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << W << " " << H << "\n255\n";
    for (auto& c : framebuffer) {
        ofs.put(char(c.r));
        ofs.put(char(c.g));
        ofs.put(char(c.b));
    }
    std::cout << "Saved " << filename << "\n";
}
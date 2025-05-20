# 3D Cube Renderer

A simple 3D rendering engine that displays three colored cubes in a scene. The program uses a software rasterizer to draw the cubes with different transformations: one in the original position, one translated, and one scaled.

## Features

- Custom software rasterizer implementation
- 3D transformation (rotation, translation, scaling)
- Back-face culling for improved performance
- Depth buffering for proper 3D occlusion
- PPM image output format

## Implementation Details

The renderer uses a simple 3D pipeline:
- Vertex transformation
- Projection to screen space
- Triangle rasterization with depth testing
- Back-face culling

## Usage

Compile the program with your C++ compiler:

```bash
g++ *.cpp -o cube_renderer -std=c++11
```

Run the program:

```bash
./cube_renderer
```

This will generate an `output.ppm` file containing the rendered image.

## File Structure

- `Main.cpp` - Main program entry point
- `Rasterizer.h/cpp` - Rasterization engine
- `Model.h/cpp` - 3D model representation
- `Vector.h/cpp` - Vector math operations
- `Transform.h/cpp` - 3D transformation functions
- `Instance.h/cpp` - Scene object instances
- `Triangle.h` - Triangle primitive
- `Color.h` - RGB color representation
- `Constant.h` - Mathematical constants

## Requirements

- C++11 compatible compiler
- Standard C++ libraries

## Output

The program generates a PPM image file named `output.ppm` containing three cubes:
- An original cube
- A translated cube 
- A scaled cube (1.5x larger)

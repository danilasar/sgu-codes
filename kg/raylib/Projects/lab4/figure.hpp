#pragma once

#include "matrix.hpp"

#include <vector>

namespace ssu {

struct Path {
    std::vector<Vec2> vertices;
    Color color;
    float thickness;

    Path(std::vector<Vec2> vertices, Color color, float thickness)
        : vertices(vertices)
        , color(color)
        , thickness(thickness) {}
};

struct Figure {
    std::vector<Path> paths;
    float Vx, Vy;

    Figure() = default;

    Figure(std::vector<Path> paths, float Vx, float Vy)
        : paths(paths)
        , Vx(Vx)
        , Vy(Vy) {}
};

} // namespace ssu

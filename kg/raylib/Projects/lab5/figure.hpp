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
	Mat3 M;

    Figure() = default;

    Figure(std::vector<Path> paths, float Vx, float Vy, Mat3 M)
    //Figure(std::vector<Path> paths, Mat3 M)
        : paths(paths)
		, Vx(Vx)
		, Vy(Vy)
		, M(M) {}
};

struct Model {
	std::vector<Figure> figures;
	float Vx, Vy;
	
	Model() = default;

	//Model(std::vector<Figure> figures, float Vx, float Vy, Mat3 M)
	Model(std::vector<Figure> figures, float Vx, float Vy)
		: figures(figures)
		, Vx(Vx)
		, Vy(Vy) {}
};


} // namespace ssu

#pragma once
#include <vector>
#include <glm/glm.hpp>
#ifndef GLAD_INCLUDED
#define GLAD_INCLUDED
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

class path {
public:
    std::vector<glm::vec3> vertices; // точки ломаной
    glm::vec3 color;                 // цвет RGB (0..1)
    float thickness;                 // толщина линии
    GLuint vertexArray;              // VAO
    GLuint vertexBuffer;             // VBO
    path(std::vector<glm::vec3> verts, glm::vec3 col, float thickn)
        : vertices(verts), color(col), thickness(thickn)
    {
        setupPath();
    }

private:
    void setupPath();
};

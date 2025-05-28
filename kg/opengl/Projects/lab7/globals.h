#pragma once
#define GLFW_INCLUDE_NONE
#include <vector>
#include <GLFW/glfw3.h>
#ifndef GLAD_INCLUDED
#define GLAD_INCLUDED
#include <glad/glad.h>
#endif
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <gtk/gtk.h>
#include "read_from_file.h"
#include "shader.h"
#include "model.h"

//=============================================================================
// ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ
//=============================================================================
extern std::vector<model> models;
extern glm::mat4 T; // матрица, в которой накапливаются все преобразования
extern glm::vec3 S, P, u; // координаты точки наблюдения
// точки, в которую направлен вектор наблюдения
// вектора направления вверх
extern float dist; // вспомогательная переменная - расстояние между S и P
extern float fovy, aspect; // угол обзора и соотношение сторон окна наблюдения
extern float fovy_work, aspect_work; // рабочие переменные для fovy и aspect
extern float near_view, far_view; // расстояния до окна наблюдения и до горизонта
extern float n, f; // рабочие переменные для near_view и far_view
extern float l, r, t, b; // рабочие вспомогательные переменные
// для значений координат левой, правой,
// нижней и верхней коорднаты в СКН
enum projType { Ortho, Frustum, Perspective };
extern projType pType; // тип трехмерной проекции
extern double lastX, lastY; // последняя позиция курсора
extern bool action;
//=============================================================================

void init_work_pars();
glm::mat4 rotateP(float theta, glm::vec3 n, glm::vec3 P);
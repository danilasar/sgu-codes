#pragma once

#include <string>
#include "globals.h"

enum ShaderType {
    VERTEX,
    FRAGMENT
};

GLuint compile_shader(const GLchar* source, ShaderType type);
GLuint initialize_shaders(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource);

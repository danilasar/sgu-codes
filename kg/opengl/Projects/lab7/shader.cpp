#include "shader.h"
#include <iostream>
#include <string>

GLuint compile_shader(const GLchar* source, ShaderType type) {
    GLuint shader;
    switch(type) {
        case VERTEX:
            shader = glCreateShader(GL_VERTEX_SHADER);
            break;
        case FRAGMENT:
            shader = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            throw std::runtime_error("Unknown shader type");
    }
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLchar info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::string str_name;
        switch(type) {
            case VERTEX: str_name = "VERTEX"; break;
            case FRAGMENT: str_name = "FRAGMENT"; break;
            default: str_name = "UNDEFINED_SHADER"; break;
        }
        std::cerr << "ERROR::SHADER::" << str_name << "::COMPILATION_FAILED\n" << info_log << std::endl;
    }
    return shader;
}

GLuint initialize_shaders(const GLchar* vertexShaderSource, const GLchar* fragmentShaderSource) {
    auto vertexShader = compile_shader(vertexShaderSource, VERTEX);
    auto fragmentShader = compile_shader(fragmentShaderSource, FRAGMENT);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
        glDeleteProgram(shaderProgram);
        return 0;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

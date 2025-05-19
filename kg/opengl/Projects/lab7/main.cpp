#include <cstring>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//=====================================================================
// ВЕРШИННЫЙ ШЕЙДЕР
//=====================================================================
const GLchar *vertexShaderSource
    = "#version 330 core\n"
      "layout (location = 0) in vec3 position;\n"
      "void main() {\n"
      "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
      "}\0";
//=====================================================================
//======================================================
// ФРАГМЕНТНЫЙ ШЕЙДЕР
//======================================================
const char *fragmentShaderSource
    = "#version 330 core\n"
      "out vec4 color;\n"
      "void main() {\n"
      "color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
      "}\n\0";

//=======================================================
const GLchar **abaunda = &vertexShaderSource;

// обработчик события Resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Обработчик нажатия клавиш
void key_callback(
    GLFWwindow *window, int key, int scancode, int action, int mode
) {
    if (action != GLFW_RELEASE) { // если клавиша нажата
        switch (key) { // анализируем обрабатываемую клавишу
        case GLFW_KEY_ESCAPE:
            // если клавиша - Escape
            // устанавливаем, что окно window должно быть закрыто
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
        }
    }
}

enum ShaderType {
    VERTEX,
    FRAGMENT
};

GLuint compile_shader(const GLchar* source, ShaderType type) {
    GLuint shader; // шейдерный объект - вершинный шейдер
    shader = glCreateShader(GL_VERTEX_SHADER); // создаем объект
    // привязываем исходный код к шейдерному объекту
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint success; // результат компиляции
    // запрашивам статус компиляции шейдера в переменную success
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        GLchar info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log); // запрашиваем сообщение
        // выводим сообщение об ошибке на экран
        std::string str_name;
        switch(type) {
            case VERTEX: str_name = "VERTEX"; break;
            case FRAGMENT: str_name = "FRAGMENT"; break;
            default: str_name = "UNDEFINED_SHADER"; break;
        }
        std::cerr << "ERROR::SHADER::" << str_name << "::COMPILATION_FAILED\n" << info_log << std::endl;
    }
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    const int window_width = 640;
    const int window_height = 480;

    const char *window_title = "Welcome to OpenGL!";

    GLFWwindow *window = glfwCreateWindow(
        window_width, window_height, window_title, NULL, NULL
    );

    if (!window) {
        std::cerr << "ERROR: can't create GLFW window: " << strerror(errno)
                  << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    // Назначение обработчика события Resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Назначение обработчика нажатия клавиш
    glfwSetKeyCallback(window, key_callback);


    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "ERROR: can't start GLAD" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, window_width, window_height);

//
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

#include <cstring>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

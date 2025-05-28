#include <cstring>
#include <iostream>

#include "globals.h"
#include "callbacks.h"

// Инициализация глобальных переменных
std::vector<model> models;
glm::mat4 T = glm::mat4(1.0f); // единичная матрица
glm::vec3 S(0.0f, 0.0f, 5.0f);  // Позиция камеры
glm::vec3 P(0.0f, 0.0f, 0.0f);  // Точка наблюдения
glm::vec3 u(0.0f, 1.0f, 0.0f);  // Вектор вверх
float dist = 5.0f; // расстояние между S и P
float fovy = glm::radians(45.0f);  // Угол обзора
float aspect = 1.0f; // соотношение сторон окна наблюдения
float fovy_work = fovy;
float aspect_work = aspect;
float near_view = 0.1f;  // Ближняя плоскость
float far_view = 100.0f; // Дальняя плоскость
float n = near_view;
float f = far_view;
float l = -1.0f; // левая координата
float r = 1.0f;  // правая координата
float t = 1.0f;  // верхняя координата
float b = -1.0f; // нижняя координата
projType pType = Perspective; // тип проекции
double lastX, lastY; // последняя позиция курсора
bool action;

glm::mat4 rotateP(float theta, glm::vec3 n, glm::vec3 P) {
    return glm::translate(P) * glm::rotate(theta, n) * glm::translate(-P);
}

void initWorkPars() { // инициализация рабочих параметров камеры
    n = near_view;
    f = far_view;
    fovy_work = fovy;
    aspect_work = aspect;
    float Vy = 2 * near_view * glm::tan(fovy / 2);
    float Vx = aspect * Vy;
    l = -Vx / 2;
    r = -l;
    b = -Vy / 2;
    t = -b;
    dist = glm::length(P - S);
    T = glm::lookAt(S, P, u);
}


//=====================================================================
// ВЕРШИННЫЙ ШЕЙДЕР
//=====================================================================
const GLchar *vertexShaderSource
    = "#version 330 core\n"
      "layout (location = 0) in vec3 position;\n"
      "uniform mat4 clipView;\n"
      "void main() {\n"
      "gl_Position = clipView * vec4(position, 1.0);\n"
      "}\0";
//=====================================================================
//======================================================
// ФРАГМЕНТНЫЙ ШЕЙДЕР
//======================================================
const char *fragmentShaderSource
    = "#version 330 core\n"
      "out vec4 color;\n"
      "uniform vec3 pathColor;\n"
      "void main() {\n"
      "color = vec4(pathColor, 1.0f);\n"
      "}\n\0";

//=======================================================

int main() {
    gtk_init(0, NULL);
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
    // Назначение обработчиков событий
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // Назначение обработчика нажатия клавиш
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "ERROR: can't start GLAD" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, window_width, window_height);

    GLuint shaderProgram = initialize_shaders(vertexShaderSource, fragmentShaderSource);
    if (shaderProgram == 0) {
        std::cerr << "Failed to initialize shaders" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Получаем локации uniform-переменных
    GLint pathColorLocation = glGetUniformLocation(shaderProgram, "pathColor");
    GLint clipViewLocation = glGetUniformLocation(shaderProgram, "clipView");

    read_from_file("Assets/InputFiles/lab7/triangle.txt");

    while (!glfwWindowShouldClose(window)) { // пока окно window не должно закрыться
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // назначаем цвет заливки
        glClear(GL_COLOR_BUFFER_BIT); // очищаем буфер заданным цветом

        glUseProgram(shaderProgram); // шейдерную программу shaderProgram делаем активной

        glm::mat4 proj; // матрица перехода в пространство отсечения
        switch (pType) {
        case Ortho: // прямоугольная проекция
            proj = glm::ortho(l, r, b, t, n, f);
            break;
        case Frustum: // перспективная проекция с Frustum
            proj = glm::frustum(l, r, b, t, n, f);
            break;
        case Perspective: // перспективная проекция с Perspective
            proj = glm::perspective(fovy_work, aspect_work, n, f);
            break;
        }
        glm::mat4 C = proj * T; // матрица перехода от мировых координат в пространство отсечения
        for (size_t k = 0; k < models.size(); k++) { // цикл по моделям
            std::vector<path> paths = models[k].paths; // список ломаных очередной модели
            glm::mat4 TM = C * models[k].transform; // матрица общего преобразования модели
            // пересылка пересылка матрицы TM в переменную clipView шейдерной программы
            glUniformMatrix4fv(clipViewLocation, 1, GL_FALSE, glm::value_ptr(TM));
            for (size_t i = 0; i < paths.size(); i++) {
                // пересылка цвета линии в переменную pathColor шейдерной программы
                glUniform3fv(pathColorLocation, 1, glm::value_ptr(paths[i].color));
                glBindVertexArray(paths[i].vertexArray); // делаем активным вершинный массив i-й ломаной
                glLineWidth(paths[i].thickness); // устанавливаем толщину линии
                glDrawArrays(GL_LINE_STRIP, 0, paths[i].vertices.size()); // отрисовка ломаной
                glBindVertexArray(0); // отключаем вершинный массив
            }
        }

        glfwSwapBuffers(window); // поменять местами буферы изображения
        glfwPollEvents(); // проверить, произошли ли какие-то события
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

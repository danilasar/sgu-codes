#include "callbacks.h"
#include <iostream>
#include <cmath>

// обработчик события Resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    dist += yoffset;
}

void cursor_pos_save_callback(GLFWwindow* window, double xpos, double ypos) {
    // для обработки нажатия мыши для вращения
    if (action) {
        glm::vec3 n = glm::vec3(lastY - ypos, lastX - xpos, 0);
        glm::mat4 M = rotate_p(0.1, n, glm::vec3(0, 0, -dist));
        glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0);
        glm::vec3 s_new = glm::vec3(M * glm::vec4(0, 0, 0, 1));
        glm::vec3 P = M * glm::vec4(0, 0, -1, 1);
        T = lookAt(s_new, P, u_new) * T;
    }
    lastX = xpos;
    lastY = ypos;
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    // вычисляем вектор, задающий ось вращения
    glm::vec3 n = glm::vec3(lastY - ypos, lastX - xpos, 0);
    // создаем матрицу вращения
    glm::mat4 M = glm::rotate(glm::length(n) * 0.002f, n);
    // вращаем току (0, 0, -1), на которую смотрит наблюдатель
    glm::vec3 P = M * glm::vec4(0, 0, -1, 1);
    // добавляем к преобразованиям переход к новой системе координат наблюдателя
    T = glm::lookAt(glm::vec3(0), P, glm::vec3(0, 1, 0)) * T;
    lastX = xpos;
    lastY = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
            action = true;
        else if (action == GLFW_RELEASE)
			action = false;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) { // 6
    if (action != GLFW_RELEASE) { // если клавиша нажата
        switch (key) { // анализируем обрабатываемую клавишу
        case GLFW_KEY_ESCAPE: // если клавиша - Escape
            init_work_pars();
            break;
        case GLFW_KEY_W:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(0, 0, -0.1), glm::vec3(0, 0, -0.2), glm::vec3(0, 0.1, 0)) * T;
            }
            else
            {
                T = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, -2), glm::vec3(0, 1, 0)) * T;
            }
            break;
        case GLFW_KEY_S:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(0, 0, -0.1), glm::vec3(0, 0, 0), glm::vec3(0, 0.1, 0)) * T;
            }
            else
            {
                T = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)) * T;
            }
            break;
        case GLFW_KEY_A:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(-0.1, 0, 0), glm::vec3(-0.1, 0, -0.1), glm::vec3(0, 0.1, 0)) * T;
            }
            else
            {
                T = glm::lookAt(glm::vec3(-1, 0, 0), glm::vec3(-1, 0, -1), glm::vec3(0, 1, 0)) * T;
            }
            break;
        case GLFW_KEY_D:
            if (mode == GLFW_MOD_SHIFT) {
                T = glm::lookAt(glm::vec3(0.1, 0, 0), glm::vec3(0.1, 0, -0.1), glm::vec3(0, 0.1, 0)) * T;
            }
            else
            {
                T = glm::lookAt(glm::vec3(1, 0, 0), glm::vec3(1, 0, -1), glm::vec3(0, 1, 0)) * T;
            }
            break;
        case GLFW_KEY_R: {
            glm::vec3 u_new = glm::mat3(glm::rotate(0.1f, glm::vec3(0, 0, 1))) * glm::vec3(0, 1, 0);
            T = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), u_new) * T;
            break;
        }
        case GLFW_KEY_Y: {
            glm::vec3 u_new = glm::mat3(glm::rotate(-0.1f, glm::vec3(0, 0, 1))) * glm::vec3(0, 1, 0);
            T = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), u_new) * T;
            break;
        }
        case GLFW_KEY_T: {
            if (mode == GLFW_MOD_SHIFT) {
                // матрица вращения относительно точки P
                glm::mat4 M = rotateP(0.1, glm::vec3(1, 0, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
                // переход к СКН в которой начало координат в новой точке, а направление
                // наблюдения - в точку P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(0.1f, glm::vec3(1, 0, 0)); // матрица вращения относительно Ox
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                // вращение точки, в которую смотрит наблюдатель
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_G: {
            if (mode == GLFW_MOD_SHIFT) {
                // матрица вращения относительно точки P
                glm::mat4 M = rotateP(-0.1, glm::vec3(1, 0, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
                // переход к СКН в которой начало координат в новой точке, а направление
                // наблюдения - в точку P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(-0.1f, glm::vec3(1, 0, 0)); // матрица вращения относительно Ox
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                // вращение точки, в которую смотрит наблюдатель
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_F: {
            if (mode == GLFW_MOD_SHIFT) {
                // матрица вращения относительно точки P
                glm::mat4 M = rotateP(0.1, glm::vec3(0, 1, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
                // переход к СКН в которой начало координат в новой точке, а направление
                // наблюдения - в точку P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(0.1f, glm::vec3(0, 1, 0)); // матрица вращения относительно Ox
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                // вращение точки, в которую смотрит наблюдатель
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_H: {
            if (mode == GLFW_MOD_SHIFT) {
                // матрица вращения относительно точки P
                glm::mat4 M = rotateP(-0.1, glm::vec3(0, 1, 0), glm::vec3(0, 0, -dist));
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                glm::vec3 S_new = glm::vec3(M * glm::vec4(0, 0, 0, 1)); // вращение начала координат
                // переход к СКН в которой начало координат в новой точке, а направление
                // наблюдения - в точку P
                T = glm::lookAt(S_new, glm::vec3(0, 0, -dist), u_new) * T;
            }
            else {
                glm::mat4 M = glm::rotate(-0.1f, glm::vec3(0, 1, 0)); // матрица вращения относительно Ox
                glm::vec3 u_new = glm::mat3(M) * glm::vec3(0, 1, 0); // вращение направления вверх
                // вращение точки, в которую смотрит наблюдатель
                glm::vec3 P_new = glm::vec3(M * glm::vec4(0, 0, -1, 1));
                T = glm::lookAt(glm::vec3(0, 0, 0), P_new, u_new) * T;
            }
            break;
        }
        case GLFW_KEY_I:
            if (mode == GLFW_MOD_SHIFT) {
                t -= 1;
            }
            else {
                t += 1;
            }
            break;
        case GLFW_KEY_J:
            if (mode == GLFW_MOD_SHIFT) {
                l += 1;
            }
            else {
                l -= 1;
            }
            break;
        case GLFW_KEY_K:
            if (mode == GLFW_MOD_SHIFT) {
                b -= 1;
            }
            else {
                b += 1;
            }
            break;
        case GLFW_KEY_L:
            if (mode == GLFW_MOD_SHIFT) {
                r += 1;
            }
            else {
                r -= 1;
            }
            break;
        case GLFW_KEY_U:
            if (mode == GLFW_MOD_SHIFT) {
                if (n >= 0.3) n -= 0.2;
            }
            else {
                if (n <= f - 0.3) n += 0.2;
            }
            break;
        case GLFW_KEY_O:
            if (mode == GLFW_MOD_SHIFT) {
                if (f >= n + 0.3) f -= 0.2;
            }
            else {
                f += 0.2;
            }
            break;
        case GLFW_KEY_B:
            if (mode == GLFW_MOD_SHIFT) {
                if (dist >= 0.3) dist -= 0.2;
            }
            else {
                dist += 0.2;
            }
            break;
        case GLFW_KEY_Z:
            if (mode == GLFW_MOD_SHIFT) {
                if (fovy_work >= 0.08)
                    fovy_work -= 0.05;
            }
            else {
                if (fovy_work <= 2.95)
                    fovy_work += 0.05;
            }
            break;
        case GLFW_KEY_X:
            if (mode == GLFW_MOD_SHIFT) {
                if (aspect_work >= 0.06)
                    aspect_work -= 0.05;
            }
            else {
                aspect_work += 0.05;
            }
            break;
        case GLFW_KEY_1:
            pType = Ortho;
            break;
        case GLFW_KEY_2:
            pType = Frustum;
            break;
        case GLFW_KEY_3:
            pType = Perspective;
            break;
        case GLFW_KEY_F3: {
            GtkWidget *dialog = nullptr;
            gchar *filename = nullptr;
            
            // Create dialog with error handling
            dialog = gtk_file_chooser_dialog_new("Open File",
                                                 GTK_WINDOW(nullptr), // Use actual parent if available
                                                 GTK_FILE_CHOOSER_ACTION_OPEN,
                                                 "_Cancel", GTK_RESPONSE_CANCEL,
                                                 "_Open", GTK_RESPONSE_ACCEPT,
                                                 nullptr);
            
            if (!dialog) {
                std::cerr << "Error creating GTK file dialog" << std::endl;
                return;
            }
            
            // Set current folder
            if (!gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir())) {
                std::cerr << "Error setting current folder to home directory" << std::endl;
            }
            
            // Run dialog and handle response
            int response = gtk_dialog_run(GTK_DIALOG(dialog));

            gtk_widget_hide(dialog);

            gdk_flush();
            while (gtk_events_pending()) {
                gtk_main_iteration_do(false);
            }
            
            switch (response) {
                case GTK_RESPONSE_ACCEPT:
                    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
                    if (filename) {
                        read_from_file(filename);
                        g_free(filename);
                        filename = nullptr;
                    }
                    break;
                case GTK_RESPONSE_CANCEL:
                case GTK_RESPONSE_DELETE_EVENT:
                default:
                    std::cout << "File loading was cancelled" << std::endl;
                    break;
            }
            
            // Clean up resources - this should happen automatically after gtk_dialog_run()
            // but explicit cleanup ensures proper resource management
            gtk_widget_destroy(dialog);
            dialog = nullptr;
            
            break;
        }
        case GLFW_KEY_F5:
            if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                glfwSetCursorPosCallback(window, cursor_pos_save_callback);
            }
            else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                glfwSetCursorPosCallback(window, cursor_pos_callback);
            }
            break;

        default:
            break;
        }
    }
}

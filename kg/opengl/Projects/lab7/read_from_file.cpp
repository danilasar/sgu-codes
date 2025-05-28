#include "read_from_file.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "globals.h"

void read_from_file(const char* fileName) {
    // объявление и открытие файла
    std::ifstream in;
    in.open(fileName);
    if (in.is_open()) {
        // файл успешно открыт
        models.clear(); // очищаем имеющийся список рисунков
        // временные переменные для чтения из файла
        glm::mat4 M = glm::mat4(1.f); // матрица для получения модельной матрицы
        glm::mat4 initM; // матрица для начального преобразования каждого рисунка
        std::vector<glm::mat4> transforms; // стек матриц преобразований
        std::vector<path> figure; // список ломаных очередного рисунка
        float thickness = 2; // толщина со значением по умолчанию 2
        float r, g, b; // составляющие цвета
        r = g = b = 0; // значение составляющих цвета по умолчанию (черный)
        std::string cmd; // строка для считывания имени команды
        // непосредственно работа с файлом
        std::string str; // строка, в которую считываем строки файла
        std::getline(in, str); // считываем из входного файла первую строку
        while (in) { // если очередная строка считана успешно
            // обрабатываем строку
            if ((str.find_first_not_of(" \t\r\n") != std::string::npos) && (str[0] != '#')) {
                // прочитанная строка не пуста и не комментарий
                std::stringstream s(str); // строковый поток из строки str
                s >> cmd;
                if (cmd == "camera") { // положение камеры
                    float x, y, z;
                    s >> x >> y >> z; // координаты точки наблюдения
                    S = glm::vec3(x, y, z);
                    s >> x >> y >> z; // точка, в которую направлен вектор наблюдения
                    P = glm::vec3(x, y, z);
                    s >> x >> y >> z; // вектор направления вверх
                    u = glm::vec3(x, y, z);
                }
                else if (cmd == "screen") { // положение окна наблюдения
                    s >> fovy_work >> aspect >> near_view >> far_view; // параметры команды
                    fovy = glm::radians(fovy_work); // перевод угла из градусов в радианты
                }
                else if (cmd == "color") { // цвет линии
                    s >> r >> g >> b; // считываем три составляющие цвета
                }
                else if (cmd == "thickness") { // толщина линии
                    s >> thickness; // считываем значение толщины
                }
                else if (cmd == "path") { // набор точек
                    std::vector<glm::vec3> vertices; // список точек ломаной
                    int N; // количество точек
                    s >> N;
                    std::string str1; // дополнительная строка для чтения из файла
                    while (N > 0) { // пока не все точки считали 
                        std::getline(in, str1); // считываем в str1 из входного файла очередную строку
                        // так как файл корректный, то на конец файла проверять не нужно
                        if ((str1.find_first_not_of(" \t\r\n") != std::string::npos) && (str1[0] != '#')) {
                            // прочитанная строка не пуста и не комментарий
                            // значит в ней пара координат
                            float x, y, z; // переменные для считывания
                            std::stringstream s1(str1); // еще один строковый поток из строки str1
                            s1 >> x >> y >> z;
                            vertices.push_back(glm::vec3(x, y, z)); // добавляем точку в список
                            N--; // уменьшаем счетчик после успешного считывания точки
                        }
                    }
                    // все точки считаны, генерируем ломаную (path) и кладем ее в список figure
                    figure.push_back(path(vertices, glm::vec3(r, g, b) / 255.f, thickness));
                }
                else if (cmd == "model") { // начало описания нового рисунка
                    float mVcx, mVcy, mVcz, mVx, mVy, mVz; // параметры команды model
                    s >> mVcx >> mVcy >> mVcz >> mVx >> mVy >> mVz; // считываем значения переменных
                    float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
                    // сдвиг точки привязки из начала координат в нужную позицию
                    // после которого проводим масштабирование
                    initM = glm::scale(glm::vec3(S)) * glm::translate(glm::vec3(-mVcx, -mVcy, -mVcz));
                    figure.clear();
                }
                else if (cmd == "figure") { // формирование новой модели
                    models.push_back(model(figure, M * initM));
                }
                else if (cmd == "translate") { // перенос
                    float Tx, Ty, Tz; // параметры преобразования переноса
                    s >> Tx >> Ty >> Tz; // считываем параметры
                    M = glm::translate(glm::vec3(Tx, Ty, Tz)) * M; // добавляем перенос к общему преобразованию
                }
                else if (cmd == "scale") { // масштабирование
                    float S; // параметр масштабирования
                    s >> S; // считываем параметр
                    M = glm::scale(glm::vec3(S)) * M; // добавляем масштабирование к общему преобразованию
                }
                else if (cmd == "rotate") { // поворот
                    float theta; // угол поворота в градусах
                    float nx, ny, nz; // координаты направляющего вектора оси вращения
                    s >> theta >> nx >> ny >> nz; // считываем параметры
                    // добавляем вращение к общему преобразованию
                    M = glm::rotate(glm::radians(theta), glm::vec3(nx, ny, nz)) * M;
                }
                else if (cmd == "pushTransform") { // сохранение матрицы в стек
                    transforms.push_back(M); // сохраняем матрицу в стек
                }
                else if (cmd == "popTransform") { // откат к матрице из стека
                    M = transforms.back(); // получаем верхний элемент стека
                    transforms.pop_back(); // выкидываем матрицу из стека
                }
            }
            // считываем очередную строку
            std::getline(in, str);
        }
        init_work_pars();
    }
}

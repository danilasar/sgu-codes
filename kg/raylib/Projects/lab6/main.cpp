#include "matrix.hpp"
#include "transform.hpp"
#include "figure.hpp"

#include <raylib.h>
#include <raygui.h>
#include <nfd.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cfloat>

Mat4 T, initT;
Vec3 S, P, u; // координаты точки наблюдения
// точки, в которую направлен вектор наблюдения
// вектора направления вверх
float dist; // вспомогательная переменная - расстояние между S и P
float fovy, aspect; // угол обзора и соотношение сторон окна наблюдения
float fovy_work, aspect_work; // рабочие переменные для fovy и aspect
float near, far; // расстояния до окна наблюдения и до горизонта
float n, f;      // рабочие переменные для near и far
float l, r, t, b; // рабочие вспомогательные переменные

// для значений координат левой, правой,
// нижней и верхней координаты в СКН
enum projType { Ortho, Frustum, Perspective } pType; // тип трехмерной проекции

bool isIgnorableLine(const std::string &line) {
    return line.find_first_not_of(" \t\r\n") == std::string::npos
        || line.front() == '#';
}

void initWorkPars() { // инициализация рабочих параметров камеры
    n = near;
    f = far;
    fovy_work = fovy;
    aspect_work = aspect;
    float Vy = 2 * near * tan(fovy / 2);
    float Vx = aspect * Vy;
    l = -Vx / 2;
    r = Vx / 2;
    b = -Vy / 2;
    t = Vy / 2;
    dist = length(P - S);
    T = look_at(S, P, u);
}

ssu::Model readFromFile(const char *fileName) {
    std::ifstream in(fileName);

    // NOTE: После изменения типа возвращаемого значения с void на Figure, этот
    // код стал мешаться. По хорошему тут должен быть Optional или исключение.
    // Учитывая, что в остальном коде этой функции не предполагаются ошибки,
    // я его просто оставил на память.
#if 0
	if (!in.is_open()) {
		std::cerr << "ERROR: can't open file: \"" << fileName << "\""
				  << std::endl;
		return;
	}
#endif

    ssu::Model model;
    // NOTE: как же я ненавижу C++!!! По историческим(??) причинам cin и ss
    // считывают в переменные char ASCII (!!!!!!) код введённого символа, вместо
    // парсинга 8-битного числа. Отсюда здесь int и ниже static_cast на три
    // переменные (?!?!?!?!?).
    int r, g, b;
    float thickness;
    float mVx = 0, mVy = 0;
    std::vector<ssu::Path> paths;
    Mat4 M = Mat4(1.f);
    Mat4 initM;
    std::vector<Mat4> transforms;
    ssu::Figure figure;

    std::string line;
    while (in) {
        getline(in, line);
        if (isIgnorableLine(line)) {
            continue;
        }

        std::stringstream s(line);
        std::string cmd;

        s >> cmd;
        if (cmd == "camera") { // положение камеры
            s >> S.x >> S.y >> S.z; // координаты точки наблюдения
            s >> P.x >> P.y
                >> P.z; // точка, в которую направлен вектор наблюдения
            s >> u.x >> u.y >> u.z; // вектор направления вверх
        } else if (cmd == "screen") { // положение окна наблюдения
            s >> fovy_work >> aspect >> near >> far; // параметры команды
            fovy = fovy_work / 180.f
                 * M_PI; // перевод угла из градусов в радианты
        } else if (cmd == "color") { // цвет линии
            s >> r >> g >> b; // считываем три составляющие цвета
        } else if (cmd == "thickness") { // толщина линии
            s >> thickness; // считываем значение толщины
        } else if (cmd == "path") {     // набор точек
            std::vector<Vec3> vertices; // список точек ломаной
            int N;                      // количество точек
            s >> N;
            std::string str1; // дополнительная строка для чтения из файла
            while (N > 0) { // пока не все точки считали
                getline(
                    in, str1
                ); // считываем в str1 из входного файла очередную строку
                // так как файл корректный, то на конец файла проверять не нужно
                if ((str1.find_first_not_of(" \t\r\n") != std::string::npos)
                    && (str1[0] != '#'))
                {
                    // прочитанная строка не пуста и не комментарий
                    // значит в ней пара координат
                    float x, y, z; // переменные для считывания
                    std::stringstream s1(str1
                    ); // еще один строковый поток из строки str1
                    s1 >> x >> y >> z;
                    vertices.push_back(Vec3(x, y, z)
                    );   // добавляем точку в список
                    N--; // уменьшаем счетчик после успешного считывания точки
                }
            }
            // все точки считаны, генерируем ломаную (path) и кладем ее в список
            // figure
            figure.paths.push_back(ssu::Path(
                vertices,
                Color(
                    static_cast<uint8_t>(r),
                    static_cast<uint8_t>(g),
                    static_cast<uint8_t>(b),
                    255
                ),
                thickness
            ));
        } else if (cmd == "model") { // начало описания нового рисунка
            float mVcx, mVcy, mVcz, mVx, mVy, mVz; // параметры команды model
            s >> mVcx >> mVcy >> mVcz >> mVx >> mVy
                >> mVz; // считываем значения переменных
            float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
            // сдвиг точки привязки из начала координат в нужную позицию
            // после которого проводим масштабирование
            initM = scale(S, S, S) * translate(-mVcx, -mVcy, -mVcz);
            figure.paths.clear();
        } else if (cmd == "figure") { // формирование новой модели
            figure.M = M * initM;
            figure.Vx = mVx;
            figure.Vy = mVy;
            model.figures.push_back(figure);
        } else if (cmd == "translate") { // перенос
            float Tx, Ty, Tz; // параметры преобразования переноса
            s >> Tx >> Ty >> Tz; // считываем параметры
            M = translate(Tx, Ty, Tz)
              * M; // добавляем перенос к общему преобразованию
        } else if (cmd == "scale") { // масштабирование
            float S; // параметр масштабирования
            s >> S;  // считываем параметр
            M = scale(S, S, S)
              * M; // добавляем масштабирование к общему преобразованию
        } else if (cmd == "rotate") { // поворот
            float theta;      // угол поворота в градусах
            float nx, ny, nz; // координаты направляющего вектора оси вращения
            s >> theta >> nx >> ny >> nz; // считываем параметры
            // добавляем вращение к общему преобразованию
            M = rotate(theta / 180.f * M_PI, Vec3(nx, ny, nz)) * M;
        } else if (cmd == "pushTransform") { // сохранение матрицы в стек
            transforms.push_back(M); // сохраняем матрицу в стек
        } else if (cmd == "popTransform") { // откат к матрице из стека
            M = transforms.back(); // получаем верхний элемент стека
            transforms.pop_back(); // выкидываем матрицу из стека
        }
    }
    initWorkPars();
    return model;
}

float clamp(float value, float min, float max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

char codeKS(const Vec2 &P, const Vec2 &min, const Vec2 &max) {
    char code = 0;

    if (P.x < min.x) {
        code |= 1;
    } else if (P.x > max.x) {
        code |= 2;
    }

    if (P.y < min.y) {
        code |= 4;
    } else if (P.y > max.y) {
        code |= 8;
    }

    return code;
}

bool clip(Vec2 &A, Vec2 &B, const Vec2 &min, const Vec2 &max) {
    char codeA = codeKS(A, min, max);
    char codeB = codeKS(B, min, max);

    while (codeA | codeB) {
        if (codeA & codeB) {
            return false;
        }
        if (codeA == 0) {
            std::swap(A, B);
            std::swap(codeA, codeB);
        }

        if (codeA & 1) { // A левее области видимости
            A.y = A.y + (B.y - A.y) * (min.x - A.x) / (B.x - A.x);
            A.x = min.x;
        } else if (codeA & 2) { // A правее области видимости
            A.y = A.y + (B.y - A.y) * (max.x - A.x) / (B.x - A.x);
            A.x = max.x;
        } else if (codeA & 4) { // A ниже области видимости
            A.x = A.x + (B.x - A.x) * (min.y - A.y) / (B.y - A.y);
            A.y = min.y;
        } else { // A выше области видимости
            A.x = A.x + (B.x - A.x) * (max.y - A.y) / (B.y - A.y);
            A.y = max.y;
        }
        codeA = codeKS(A, min, max);
    }
    return true;
}

inline Mat3
cadrRL(const Vec2 &Vc, const Vec2 &V, const Vec2 &Wc, const Vec2 &W) {
    return translate(Wc.x, Wc.y)
         * (scale(W.x / V.x, -W.y / V.y) * translate(-Vc.x, -Vc.y));
}

struct Padding {
    float left, right, top, bottom;
};

void frame_calc(
    const Padding &p,
    float &Wx,
    float &Wy,
    float &Wcx,
    float &Wcy,
    float &frameAspect
) {
    Wx = static_cast<float>(GetScreenWidth()) - p.left - p.right;
    Wy = static_cast<float>(GetScreenHeight()) - p.top - p.bottom;
    Wcx = p.left;
    Wcy = p.top + Wy;
    frameAspect = Wx / Wy;
}

int main() {
    if (NFD_Init() != NFD_OKAY) {
        std::cerr << "ERROR: can't initialize Native File Dialog" << std::endl;
        return EXIT_FAILURE;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "Lab seis");
    SetTargetFPS(60);

    ssu::Model model;
    Mat4 initT = Mat4(1.);

    Mat4 proj; // матрица перехода в пространство отсечения
    pType = Ortho; // WARN: самовольно

    const Padding paddings
        = {30.f, 160.f, 20.f, 50.f}; // расстояния от границ окна
    float Wx, Wy, Wcx, Wcy, frameAspect;
    frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);

    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);
        }
        switch (pType) {
        case Ortho: // прямоугольная проекция
            proj = ortho(l, r, b, t, -n, -f);
            break;
        case Frustum: // перспективная проекция с Frustum
            proj = frustum(l, r, b, t, n, f);
            break;
        case Perspective: // перспективная проекция с Perspective
            proj = perspective(fovy_work, aspect_work, n, f);
            break;
        }

        // Render figures
        BeginDrawing();
        ClearBackground(SKYBLUE);

        DrawRectangleLinesEx(
            {
                paddings.left, // слева
                paddings.top,  // сверху
                Wx,            // ширина
                Wy             // высота
            },
            2.f,
            BLACK
        );

        // матрица кадрирования
        Mat3 cdr = cadrRL(
            Vec2(-1.f, -1.f), Vec2(2.f, 2.f), Vec2(Wcx, Wcy), Vec2(Wx, Wy)
        );
        Mat4 C = proj * T; // матрица перехода от мировых координат в
                           // пространство отсечения
        for (const auto &figure : model.figures) {
            Mat4 TM = C * figure.M;
            for (const auto &lines : figure.paths) {
                Vec3 start_3d = normalize(TM * Vec4(lines.vertices[0], 1));
                Vec2 start = normalize(cdr * Vec3(start_3d, 1.f));
                for (const auto &line : lines.vertices) {
                    Vec2 end_3D = normalize(TM * Vec4(line, 1));
                    Vec2 end = normalize(cdr * Vec3(end_3D, 1.f));
                    Vec2 old_end = end;
                    if (clip(start, end, {Wcx, Wcy - Wy}, {Wcx + Wx, Wcy})) {
                        DrawLineEx(
                            {start.x, start.y},
                            {end.x, end.y},
                            lines.thickness,
                            lines.color
                        );
                    }

                    start = old_end;
                }
            }
        }

        if (GuiButton(
                {static_cast<float>(GetScreenWidth()) - 140, 20, 120, 30},
                "OPEN FILE"
            ))
        {
            nfdchar_t *outPath;
            nfdfilteritem_t filterItem[2]
                = {{"Text files", "txt"}, {"All files", "*"}};
            nfdresult_t result
                = NFD_OpenDialog(&outPath, filterItem, 2, nullptr);
            if (result == NFD_OKAY) {
                model = readFromFile(outPath);
                /*const float figureAspect = model.Vx / model.Vy;
                Mat3 T1 = translate(-model.Vx / 2, -model.Vy / 2);
                const float S = figureAspect < frameAspect ? Wy / model.Vy
                                                           : Wx / model.Vx;
                Mat4 S1 = scale(S, -S, S);
                Mat4 T2 = translate(
                    Wx / 2, Wy / 2
                ); // WARN: Миронов походу знаки попутал
                initT = T2 * (S1 * T1);
                T = initT;*/
                NFD_FreePath(outPath);
            } else if (result == NFD_CANCEL) {
                std::cerr << "INFO: NFD: user pressed cancel" << std::endl;
            } else {
                std::cerr << "ERROR: " << NFD_GetError() << std::endl;
            }
        }
        EndDrawing();
        // Escape
        if (IsKeyPressed(KEY_C)) {
            initWorkPars();
        }
        // W
        if (IsKeyPressed(KEY_W)) {
            T = look_at(Vec3(0, 0, -1), Vec3(0, 0, -2), Vec3(0, 1, 0)) * T;
        }
        // S
        if (IsKeyPressed(KEY_S)) {
            T = look_at(Vec3(0, 0, 1), Vec3(0, 0, 0), Vec3(0, 1, 0)) * T;
        }
        // A
        if (IsKeyPressed(KEY_A)) {
            T = look_at(Vec3(-1, 0, 0), Vec3(-1, 0, -1), Vec3(0, 1, 0)) * T;
        }
        // R
        if (IsKeyDown(KEY_R)) {
            Vec3 u_new = Mat3(rotate(0.1f, Vec3(0, 0, 1))) * Vec3(0, 1, 0);
            T = look_at(Vec3(0, 0, 0), Vec3(0, 0, -1), u_new) * T;
        }
        // T
        if (IsKeyPressed(KEY_T)) {
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                Mat4 M = rotateP(0.1f, Vec3(1, 0, 0), Vec3(0, 0, -dist));
                Vec3 u_new = Mat3(M) * Vec3(0, 1, 0);
                Vec3 S_new = normalize(M * Vec4(0, 0, 0, 1));
                T = look_at(S_new, Vec3(0, 0, -dist), u_new) * T;
            } else {
                Mat4 M = rotate(0.1f, Vec3(1, 0, 0));
                Vec3 u_new = Mat3(M) * Vec3(0, 1, 0);
                Vec3 P_new = normalize(M * Vec4(0, 0, -1, 1));
                T = look_at(Vec3(0, 0, 0), P_new, u_new) * T;
            }
        }
        // I
        if (IsKeyDown(KEY_I)) {
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                t -= 1;
            } else {
                t += 1;
            }
        }
        // J
        if (IsKeyDown(KEY_J)) {
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                l += 1;
            } else {
                l -= 1;
            }
        }
        // D1
        if (IsKeyPressed(KEY_ONE)) {
            pType = Ortho;
        }
        // D3
        if (IsKeyPressed(KEY_THREE)) {
            pType = Perspective;
        }
        // 2 - Frustum projection
        if (IsKeyPressed(KEY_TWO)) {
            pType = Frustum;
        }

        // D - Move right in view space
        if (IsKeyPressed(KEY_D)) {
            T = translate(1, 0, 0) * T;
        }

        // Shift+W/S/A/D - Slow movement
        float shiftStep = 0.1f;
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
            if (IsKeyDown(KEY_W)) {
                T = translate(0, 0, -shiftStep) * T;
            }
            if (IsKeyDown(KEY_S)) {
                T = translate(0, 0, shiftStep) * T;
            }
            if (IsKeyDown(KEY_A)) {
                T = translate(-shiftStep, 0, 0) * T;
            }
            if (IsKeyDown(KEY_D)) {
                T = translate(shiftStep, 0, 0) * T;
            }
        }

        // Y - Rotate around Z axis
        if (IsKeyDown(KEY_Y)) {
            T = rotate(0.1f, Vec3(0, 0, 1)) * T;
        }

        // G/Shift-G - Rotate around X axis
        if (IsKeyDown(KEY_G)) {
            float angle = IsKeyDown(KEY_LEFT_SHIFT) ? -0.1f : 0.1f;
            if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
                Mat4 M = rotateP(angle, Vec3(1, 0, 0), P);
                T = M * T;
            } else {
                T = rotate(angle, Vec3(1, 0, 0)) * T;
            }
        }

        // K/Shift-K - Adjust window params
        if (IsKeyDown(KEY_K)) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                b += 1;
            } else {
                b -= 1;
            }
        }
        if (IsKeyDown(KEY_L)) {
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                r += 1;
            } else {
                r -= 1;
            }
        }

        // U/Shift-U - Adjust n parameter
        if (IsKeyDown(KEY_U)) {
            float delta = IsKeyDown(KEY_LEFT_SHIFT) ? -0.2f : 0.2f;
            n = clamp(n + delta, 0.1f, f - 0.1f);
        }

        // O/Shift-O - Adjust f parameter
        if (IsKeyDown(KEY_O)) {
            float delta = IsKeyDown(KEY_LEFT_SHIFT) ? -0.2f : 0.2f;
            f = clamp(f + delta, n + 0.1f, FLT_MAX);
        }

        // B/Shift-B - Adjust dist
        if (IsKeyDown(KEY_B)) {
            float delta = IsKeyDown(KEY_LEFT_SHIFT) ? -0.2f : 0.2f;
            dist = fmaxf(dist + delta, 0.1f);
        }

        // Z/Shift-Z - Adjust fovy_work
        if (IsKeyDown(KEY_Z)) {
            float delta = IsKeyDown(KEY_LEFT_SHIFT) ? -0.1f : 0.1f;
            fovy_work = clamp(fovy_work + delta, 0.3f, 3.0f);
        }

        // X/Shift-X - Adjust aspect_work
        if (IsKeyDown(KEY_X)) {
            float delta = IsKeyDown(KEY_LEFT_SHIFT) ? -0.05f : 0.05f;
            aspect_work = fmaxf(aspect_work + delta, 0.01f);
        }
    }
    CloseWindow();
    NFD_Quit();

    return 0;
}

#include "matrix.hpp"
#include "transform.hpp"
#include "figure.hpp"

#include "hare.hpp"

#include <raylib.h>
#include <raygui.h>
#include <nfd.h>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdint>

bool isIgnorableLine(const std::string &line) {
    return line.find_first_not_of(" \t\r\n") == std::string::npos
        || line.front() == '#';
}

ssu::Figure readFromFile(const char *fileName) {
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

    ssu::Figure figure;
    // NOTE: как же я ненавижу C++!!! По историческим(??) причинам cin и ss
    // считывают в переменные char ASCII (!!!!!!) код введённого символа, вместо
    // парсинга 8-битного числа. Отсюда здесь int и ниже static_cast на три
    // переменные (?!?!?!?!?).
    int r, g, b;
    float thickness;

    std::string line;
    while (in) {
        getline(in, line);
        if (isIgnorableLine(line)) {
            continue;
        }

        std::stringstream s(line);

        std::string cmd;
        s >> cmd;
        if (cmd == "frame") {
            s >> figure.Vx >> figure.Vy;
        } else if (cmd == "color") {
            s >> r >> g >> b;
        } else if (cmd == "thickness") {
            s >> thickness;
        } else if (cmd == "path") {
            std::vector<Vec2> vertices;
            int n;
            s >> n;
            std::string str1;
            while (n > 0) {
                getline(in, str1);
                if (isIgnorableLine(str1)) {
                    continue;
                }
                float x, y;
                std::stringstream s1(str1);
                s1 >> x >> y;
                vertices.push_back(Vec2(x, y));
                --n;
            }
            figure.paths.push_back(ssu::Path(
                vertices,
                Color{
                    static_cast<uint8_t>(r),
                    static_cast<uint8_t>(g),
                    static_cast<uint8_t>(b),
                    255
                },
                thickness
            ));
        }
    }
    return figure;
}

int main() {
    if (NFD_Init() != NFD_OKAY) {
        std::cerr << "ERROR: can't initialize Native File Dialog" << std::endl;
        return EXIT_FAILURE;
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "Lab tres");
    SetTargetFPS(60);

    ssu::Figure figure;
    Mat3 T = Mat3(1.f);
    Mat3 initT;

    while (!WindowShouldClose()) {
        const float Wx = static_cast<float>(GetScreenWidth());
        const float Wy = static_cast<float>(GetScreenHeight());
        const float Wcx = Wx / 2.0f;
        const float Wcy = Wy / 2.0f;
        const float windowAspect = Wx / Wy;

        // Render figures
        BeginDrawing();
        ClearBackground(SKYBLUE);
        for (const auto &lines : figure.paths) {
            Vec2 start = normalize(T * Vec3(lines.vertices[0], 1));
            for (const auto &line : lines.vertices) {
                const Vec2 end = normalize(T * Vec3(line, 1));
                DrawLineEx(
                    {start.x, start.y},
                    {end.x, end.y},
                    lines.thickness,
                    lines.color
                );

                start = end;
            }
        }

        if (GuiButton({Wx - 140, 20, 120, 30}, "OPEN FILE")) {
            nfdchar_t *outPath;
            nfdfilteritem_t filterItem[2]
                = {{"Text files", "txt"}, {"All files", "*"}};
            nfdresult_t result
                = NFD_OpenDialog(&outPath, filterItem, 2, nullptr);
            if (result == NFD_OKAY) {
                figure = readFromFile(outPath);
                const float figureAspect = figure.Vx / figure.Vy;
                const float S = figureAspect < windowAspect ? Wy / figure.Vy
                                                            : Wx / figure.Vx;
                const float Ty = S * figure.Vy;
                initT = translate(0, Ty) * scale(S, -S);
                T = initT;
                NFD_FreePath(outPath);
            } else if (result == NFD_CANCEL) {
                std::cerr << "INFO: NFD: user pressed cancel" << std::endl;
            } else {
                std::cerr << "ERROR: " << NFD_GetError() << std::endl;
            }
        }
        EndDrawing();

        // Handle input
        if (IsKeyPressed(KEY_C)) {
            T = initT;
        }

        if (IsKeyDown(KEY_Q)) {
            T = translate(-Wcx, -Wcy) * T;
            T = rotate(0.01f) * T;
            T = translate(Wcx, Wcy) * T;
        }
        if (IsKeyDown(KEY_E)) {
            T = translate(-Wcx, -Wcy) * T;
            T = rotate(-0.01f) * T;
            T = translate(Wcx, Wcy) * T;
        }

        if (IsKeyDown(KEY_W)) {
            T = translate(0, -1) * T;
        }
        if (IsKeyDown(KEY_S)) {
            T = translate(0, 1) * T;
        }
        if (IsKeyDown(KEY_A)) {
            T = translate(-1, 0) * T;
        }
        if (IsKeyDown(KEY_D)) {
            T = translate(1, 0) * T;
        }

        if (IsKeyPressed(KEY_R)) {
            T = translate(-Wcx, -Wcy) * T;
            T = rotate(0.05f) * T;
            T = translate(Wcx, Wcy) * T;
        }
        if (IsKeyPressed(KEY_Y)) {
            T = translate(-Wcx, -Wcy) * T;
            T = rotate(-0.05f) * T;
            T = translate(Wcx, Wcy) * T;
        }

        if (IsKeyPressed(KEY_T)) {
            T = translate(0.f, -10.f) * T;
        }
        if (IsKeyPressed(KEY_G)) {
            T = translate(0.f, 10.f) * T;
        }
        if (IsKeyPressed(KEY_F)) {
            T = translate(-10.f, 0.f) * T;
        }
        if (IsKeyPressed(KEY_H)) {
            T = translate(10.f, 0.f) * T;
        }

        if (IsKeyPressed(KEY_Z)) {
            T = translate(-Wcx, -Wcy) * T;
            T = scale(1.1f) * T;
            T = translate(Wcx, Wcy) * T;
        }
        if (IsKeyPressed(KEY_X)) {
            T = translate(-Wcx, -Wcy) * T;
            T = scale(1 / 1.1f) * T;
            T = translate(Wcx, Wcy) * T;
        }

        if (IsKeyPressed(KEY_U)) {
            T = translate(-Wcx, -Wcy) * T;
            T = mirrorX() * T;
            T = translate(Wcx, Wcy) * T;
        }
        if (IsKeyPressed(KEY_J)) {
            T = translate(-Wcx, -Wcy) * T;
            T = mirrorY() * T;
            T = translate(Wcx, Wcy) * T;
        }

        if (IsKeyPressed(KEY_I)) {
            T = translate(-Wcx, -Wcy) * T;
            T = scale(1.1f, 1.f) * T;
            T = translate(Wcx, Wcy) * T;
        }
        if (IsKeyPressed(KEY_K)) {
            T = translate(-Wcx, -Wcy) * T;
            T = scale(1 / 1.1f, 1.f) * T;
            T = translate(Wcx, Wcy) * T;
        }

        if (IsKeyPressed(KEY_O)) {
            T = translate(-Wcx, -Wcy) * T;
            T = scale(1.f, 1.1f) * T;
            T = translate(Wcx, Wcy) * T;
        }
        if (IsKeyPressed(KEY_L)) {
            T = translate(-Wcx, -Wcy) * T;
            T = scale(1.f, 1 / 1.1f) * T;
            T = translate(Wcx, Wcy) * T;
        }
    }
    CloseWindow();
    NFD_Quit();

    return 0;
}

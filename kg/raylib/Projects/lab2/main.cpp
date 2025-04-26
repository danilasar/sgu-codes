#include "hare.hpp"
#include "clown.hpp"
#include "figure.hpp"

#include <raylib.h>
#include <array>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 600, "Lab Dos");
    SetTargetFPS(60);

    std::array availableFigures = {ssu::figure::HARE, ssu::figure::CLOWN};
    size_t figureIndex = 0;
    ssu::Figure &figure = availableFigures[figureIndex];

    bool keepAspect = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        const float Wx = static_cast<float>(GetScreenWidth());
        const float Wy = static_cast<float>(GetScreenHeight());
        const float windowAspect = Wx / Wy;

        float Sx, Sy;
        if (keepAspect) {
            const float figureAspect = figure.Vx / figure.Vy;
            Sx = Sy
                = figureAspect < windowAspect ? Wy / figure.Vy : Wx / figure.Vx;
        } else {
            Sx = Wx / figure.Vx;
            Sy = Wy / figure.Vy;
        }

        const float Ty = Sy * figure.Vy;
        for (size_t i = 0; i < figure.vertices.size(); i += 4) {
            DrawLineEx(
                {Sx * figure.vertices[i], Ty - Sy * figure.vertices[i + 1]},
                {Sx * figure.vertices[i + 2], Ty - Sy * figure.vertices[i + 3]},
                2,
                BLACK
            );
        }

        if (IsKeyPressed(KEY_M)) {
            keepAspect = !keepAspect;
        }
        if (IsKeyPressed(KEY_N)) {
            figureIndex = (figureIndex + 1) % availableFigures.size();
            figure = availableFigures[figureIndex];
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

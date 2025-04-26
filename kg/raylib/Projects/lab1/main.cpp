#include <raylib.h>
#include <vector>

const char *const LETTERS =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" \
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~" \
    "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(600, 480, "Lab Uno");
    SetTargetFPS(60);

    int cnt = 0;
    int *codepoints = LoadCodepoints(LETTERS, &cnt);
    Font f = LoadFontEx("Assets/Fonts/Roboto-Bold.ttf", 100, codepoints, cnt);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        const float Wx = static_cast<float>(GetScreenWidth());
        const float Wy = static_cast<float>(GetScreenHeight());

        DrawLineEx({0, 0}, {Wx, Wy}, 6, RED);
        DrawLineEx({90, 50}, {Wx, 80}, 10, BLUE);

        DrawText("Welcome to computer graphics", 40, 350, 26, BLACK);
        DrawTextEx(
            f, "Добро пожаловать на компьютерную графику",
            {40, 380}, 26, 0, BLACK
        );

        const std::vector<Vector2> points = {
            {Wx / 3 * 2, 0},
            {Wx, Wy / 3 * 2},
            {Wx / 3, Wy},
            {0, Wy / 3},
        };

        for (size_t i = 0; i < points.size(); ++i) {
            DrawLineEx(
                points[i], points[(i + 1) % points.size()], 5, DARKGREEN
            );
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

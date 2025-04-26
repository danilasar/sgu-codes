#include <raylib.h>

int main() {
    const int Wx = 640;
    const int Wy = 480;

    InitWindow(Wx, Wy, "Welcome to RayLib!");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        const char *msg = "Welcome, Creative Coders!";
        const int fontSize = 30;
        const int x = (Wx - MeasureText(msg, fontSize)) / 2;
        const int y = (Wy - fontSize) / 2;
        DrawText(msg, x, y, fontSize, WHITE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}

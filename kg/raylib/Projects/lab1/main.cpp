#include <raylib.h>

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(640, 480, "Lab Uno");
	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		BeginDrawing();
		EndDrawing();
	}
	CloseWindow();

	return 0;
}

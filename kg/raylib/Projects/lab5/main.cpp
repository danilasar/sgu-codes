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

char codeKS(const Vec2& P, const Vec2& min, const Vec2& max) {
	char code = 0;

	if(P.x < min.x) {
		code |= 1;
	} else if(P.x > max.x) {
		code |= 2;
	}

	if(P.y < min.y) {
		code |= 4;
	} else if(P.y > max.y) {
		code |= 8;
	}

	return code;
}

bool clip(Vec2 &A, Vec2 &B, const Vec2& min, const Vec2& max) {
	char codeA = codeKS(A, min, max);
	char codeB = codeKS(B, min, max);

	while(codeA | codeB) {
		if(codeA & codeB) {
			return false;
		}
		if(codeA == 0) {
			std::swap(A, B);
			std::swap(codeA, codeB);
		}

		if(codeA & 1) { // A левее области видимости
			A.y = A.y + (B.y - A.y) * (min.x - A.x) / (B.x - A.x);
			A.x = min.x;
		} else if(codeA & 2) { // A правее области видимости
			A.y = A.y + (B.y - A.y) * (max.x- A.x) / (B.x - A.x);
			A.x = max.x;
		} else if(codeA & 4) { // A ниже области видимости
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

struct Padding {
	float left, right, top, bottom;
};

void frame_calc(const Padding& p, float& Wx, float& Wy, float& Wcx, float& Wcy, float& frameAspect) {
	Wx = static_cast<float>(GetScreenWidth()) - p.left - p.right;
	Wy = static_cast<float>(GetScreenHeight()) - p.top - p.bottom;
	Wcx = p.left;
	Wcy = p.top + Wy;
	frameAspect = Wx / Wy;
}

float f(float x) {
	return x * sin(x);
}

int main() {
	if (NFD_Init() != NFD_OKAY) {
		std::cerr << "ERROR: can't initialize Native File Dialog" << std::endl;
		return EXIT_FAILURE;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(600, 600, "Lab cuatro");
	SetTargetFPS(60);

	Mat3 T = Mat3(1.f);
	Mat3 initT;

	const Padding paddings = { 30.f, 160.f, 20.f, 50.f }; // расстояния от границ окна
	const float thickness = 1.f;
	float Wx, Wy, Wcx, Wcy, frameAspect;
	float Vx, Vy;
	Vec2 Vc = Vec2(-2.f, -2.f), V = Vec2(4.f, 4.f);
	Vec2 Vc_work, V_work;
	frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);

	T = initT = Mat3(1.f);


	while (!WindowShouldClose()) {
		if(IsWindowResized()) {
			frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);
		}

		// Render figures
		BeginDrawing();
		ClearBackground(SKYBLUE);

		DrawRectangleLinesEx({
			Wcx, // слева
			Wcy - Wy, // сверху
			Wx, // ширина
			Wy // высота
		}, 2.f, BLACK);

		Vc_work = normalize(T * Vec3(Vc, 1.f));
		V_work = Mat2(T) * V;
		Vec2 start;
		float x, y;
		x = Vc_work.x;
		y = f(x);
		std::cout << x << " " << y << std::endl;
		start.x = Wcx;
		start.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
		std::cout << start.x << " " << start.y << std::endl;
		const float delta_x = V_work.x / Wx;
		DrawCircle(start.x, start.y, 5., RED);
		
		while(start.x < Wcx + Wx) {
			Vec2 end;
			end.x = start.x + 1.f;
			x += delta_x;
			y = f(x);
			end.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
			Vec2 tmp_end = end;
			bool visible = clip(start, end, {Wcx, Wcy - Wy}, {Wcx + Wx, Wcy});
			if(visible) {
				DrawLineEx(
					{start.x, start.y},
					{end.x, end.y},
					thickness,
					BLUE
				);
			}
			start = tmp_end;
		}

		EndDrawing();

		// Handle input
		if (IsKeyPressed(KEY_C)) {
			T = initT;
		}
	}
	CloseWindow();
	NFD_Quit();

	return 0;
}

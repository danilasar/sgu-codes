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

float f(float x, float z) {
	return x * sin(sqrtf(x * x + z * z));
	//return x * x + z * z;
}

bool f_exists(float x, float z, float delta_x) {
	return true;
}

int main() {
	if (NFD_Init() != NFD_OKAY) {
		std::cerr << "ERROR: can't initialize Native File Dialog" << std::endl;
		return EXIT_FAILURE;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(600, 600, "Lab cuatro");
	SetTargetFPS(60);

	Mat4 T = Mat4(1.f);
	Mat4 initT;

	const Padding paddings = { 30.f, 160.f, 20.f, 50.f }; // расстояния от границ окна
	const float thickness = 1.f;
	float Wx, Wy, Wcx, Wcy, frameAspect;
	float Wx_work, Wy_work, Wz_work, Wcx_work, Wcy_work;
	float Wx_part = 0.6f, Wy_part = 0.6f;
	Vec3 Vc = Vec3(-2.f, -2.f, -2.f), V = Vec3(4.f, 4.f, 4.f);
	Vec3 Vc_work, V_work;

	T = initT = Mat4(1.f);


	while (!WindowShouldClose()) {
		bool need_recalculate_w = true;
		if(IsWindowResized()) {
			need_recalculate_w = true;
		}
		if(need_recalculate_w) {
			need_recalculate_w = false;
			Wx = static_cast<float>(GetScreenWidth()) - paddings.left - paddings.right;
			Wy = static_cast<float>(GetScreenHeight()) - paddings.top - paddings.bottom;
			Wcx = paddings.left;
			Wcy = paddings.top + Wy;
			frameAspect = Wx / Wy;
			Wx_work = Wx_part * Wx;
			Wy_work = Wy_part * Wy;
			Wcx_work = Wx + Wcx - Wx_work;
			Wcy_work = paddings.top + Wy_work;
			Wz_work = Wcy - Wcy_work;
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

		const float delta_z = V_work.z / Wz_work;
		const float delta_Wcx = (Wcx_work - Wcx) / Wz_work;

		Vc_work = normalize(T * Vec4(Vc, 1.f));
		V_work = Mat3(T) * V;
		const Vec3 center(
			Vc_work.x + V_work.x / 2,
			Vc_work.y + V_work.y / 2,
			Vc_work.z + V_work.z / 2
		);
		const float delta_x = V_work.x / Wx_work;

		Vec2 start;
		float x, y, z;
		z = Vc_work.z;

		while(Wcy_work <= Wcy) {
			start.x = Wcx_work;
			x = Vc_work.x;
			bool has_start = f_exists(x, z, delta_x), has_end, visible;
			if(has_start) {
				y = f(x, z);
				start.y = Wcy_work - (y - Vc_work.y) / V_work.y * Wy_work;
			}
			
			float delta_y;
			unsigned char red, green, blue;
			
			while(start.x < Wcx_work + Wx_work) {
				Vec2 end;
				end.x = start.x + 1.f;
				x += delta_x;
				has_end = f_exists(x, z, delta_x);
				if(has_end) {
					y = f(x, z);
					delta_y = (y - Vc_work.y) / V_work.y;
					end.y = Wcy_work - delta_y * Wy_work;
				}
				const Vec2 tmp_end = end;
				visible = clip(start, end, {Wcx_work, Wcy_work - Wy_work}, {Wcx_work + Wx_work, Wcy_work});
				if(has_start && has_end && visible) {
					if(delta_y > 1.f) delta_y = 1.f;
					if(delta_y < 0.f) delta_y = 0.f;
					green = 510 * delta_y;
					if(delta_y < 0.5f) {
						blue = 255 - green;
						red = 0;
					} else {
						blue = 0;
						red = green - 255;
						green = 510 - green;
					}
					DrawLineEx(
						{start.x, start.y},
						{end.x, end.y},
						thickness,
						{red, green, blue, 255}
					);
				}
				start = tmp_end;
				has_start = has_end;
			}
			Wcy_work += 1.f;
			Wcx_work -= delta_Wcx;
			z += delta_z;
		}

		EndDrawing();

		// Handle input
		if (IsKeyPressed(KEY_C)) {
			T = initT;
		}

		if(IsKeyDown(KEY_A)) {
			T = translate(-V_work.x / Wx_work, 0.f, 0.f) * T;
		}

		if(IsKeyDown(KEY_D)) {
			T = translate(V_work.x / Wx_work, 0.f, 0.f) * T;
		}

		if(IsKeyDown(KEY_F)) {
			T = translate(0.f, V_work.y / Wy_work, 0.f) * T;
		}

		if(IsKeyDown(KEY_R)) {
			T = translate(0.f, -V_work.y / Wy_work, 0.f) * T;
		}

		if(IsKeyDown(KEY_W)) {
			T = translate(0.f, 0.f, V_work.y / Wy_work) * T;
		}

		if(IsKeyDown(KEY_S)) {
			T = translate(0.f, 0.f, -V_work.y / Wy_work) * T;
		}

		if(IsKeyDown(KEY_Z)) {
			T = translate(-center.x, -center.y, center.z) * T;
			T = scale(1.1f) * T;
			T = translate(center.x, center.y, center.z) * T;
		}

		if(IsKeyDown(KEY_X)) {
			T = translate(-center.x, -center.y, center.z) * T;
			T = scale(1 / 1.1f) * T;
			T = translate(center.x, center.y, center.z) * T;
		}
	}
	CloseWindow();
	NFD_Quit();

	return 0;
}

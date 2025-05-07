#include "matrix.hpp"
#include "transform.hpp"

#include <raylib.h>
#include <raygui.h>
#include <nfd.h>
#include <iostream>
#include <sstream>

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
	//return x * sin(log(x));
	return tan(x);
}

bool f_exists(float x, float delta_x) {
	//return x > 0;
	//return cos(x) != 0.f;
	return fabs(2.f * acos(cos(x)) - M_PI) > delta_x;
}

std::string to_string_with_precision(const float a_value, const int n = 3) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

void draw_grid(
	const Vec2& Wc,
	const Vec2& W,
	const Vec2& Vc_work,
	const Vec2& V_work,
	const u_int8_t num_sect_x = 5, const u_int8_t num_sect_y = 5
) {
	for(int i = 0; i <= num_sect_x; ++i) {
		float tmp_x_coord_d = Wc.x + i * W.x / num_sect_x;
		DrawLineEx(
			{tmp_x_coord_d, Wc.y},
			{tmp_x_coord_d, Wc.y - W.y},
			1.f,
			BLACK
		);
		if(i > 0 && i < num_sect_x) {
			DrawText(
				to_string_with_precision(Vc_work.x + i * V_work.x / num_sect_x).c_str(),
				tmp_x_coord_d,
				Wc.y,
				12,
				BLACK
			);
		}
	}
	for(int i = 0; i <= num_sect_y; ++i) {
		float tmp_y_coord_d = Wc.y - i * W.y / num_sect_y;
		DrawLineEx(
			{Wc.x, tmp_y_coord_d},
			{Wc.x + W.x, tmp_y_coord_d},
			1.f,
			BLACK
		);
		if(i > 0 && i < num_sect_y) {
			DrawText(
				to_string_with_precision(Vc_work.y + i * V_work.y / num_sect_y).c_str(),
				Wc.x + W.x,
				tmp_y_coord_d,
				12,
				BLACK
			);
		}
	}
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
	Vec2 Vc = Vec2(-2.f, -2.f), V = Vec2(4.f, 4.f);
	Vec2 Vc_work, V_work;
	frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);

	T = initT = Mat3(1.f);

	u_int8_t num_sect_x = 5, num_sect_y = 5;

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
		const float delta_x = V_work.x / Wx;

		draw_grid(
			{Wcx, Wcy},
			{Wx, Wy},
			Vc_work,
			V_work,
			num_sect_x, num_sect_y
		);

		Vec2 start;
		float x, y;
		x = Vc_work.x;
		start.x = Wcx;
		bool has_start = f_exists(x, delta_x), has_end, visible;
		if(has_start) {
			y = f(x);
			start.y = Wcy - (y - Vc_work.y) / V_work.y * Wy;
		}
		
		unsigned char red, green, blue;
		float delta_y;
		
		while(start.x < Wcx + Wx) {
			Vec2 end;
			end.x = start.x + 1.f;
			x += delta_x;
			has_end = f_exists(x, delta_x);
			if(has_end) {
				y = f(x);
				delta_y = (y - Vc_work.y) / V_work.y;
				end.y = Wcy - delta_y * Wy;
			}
			const Vec2 tmp_end = end;
			visible = clip(start, end, {Wcx, Wcy - Wy}, {Wcx + Wx, Wcy});
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

		EndDrawing();

		const Vec2 center(
			Vc_work.x + V_work.x / 2,
			Vc_work.y + V_work.y / 2
		);
		const float scale_factor = 1.1f;

		// Handle input
		if (IsKeyPressed(KEY_C)) {
			T = initT;
		}

		if(IsKeyDown(KEY_W)) {
			T = translate(0.f, -V_work.y / Wy) * T;
		}

		if(IsKeyDown(KEY_S)) {
			T = translate(0.f, V_work.y / Wy) * T;
		}

		if(IsKeyDown(KEY_A)) {
			T = translate(-V_work.x / Wx, 0.f) * T;
		}

		if(IsKeyDown(KEY_D)) {
			T = translate(V_work.x / Wx, 0.f) * T;
		}

		if(T.row1.x < 1e9 && IsKeyDown(KEY_Z)) {
			T = translate(-center.x, -center.y) * T;
			T = scale(scale_factor) * T;
			T = translate(center.x, center.y) * T;
		}

		if(T.row1.x > 1e-9 && IsKeyDown(KEY_X)) {
			T = translate(-center.x, -center.y) * T;
			T = scale(1 / scale_factor) * T;
			T = translate(center.x, center.y) * T;
		}

		if (IsKeyDown(KEY_T)) V.x *= scale_factor;
		if (IsKeyDown(KEY_G)) V.x /= scale_factor;
		
		if (IsKeyDown(KEY_Y)) V.y *= scale_factor;
		if (IsKeyDown(KEY_H)) V.y /= scale_factor;

		if(IsKeyPressed(KEY_ONE)) num_sect_x += 1;

		if(num_sect_x > 2 && IsKeyPressed(KEY_TWO)) {
			num_sect_x -= 1;
		}

		if (IsKeyDown(KEY_T)) V.x *= scale_factor;
		if (IsKeyDown(KEY_G)) V.x /= scale_factor;
		
		if (IsKeyDown(KEY_Y)) V.y *= scale_factor;
		if (IsKeyDown(KEY_H)) V.y /= scale_factor;

	}
	CloseWindow();
	NFD_Quit();

	return 0;
}

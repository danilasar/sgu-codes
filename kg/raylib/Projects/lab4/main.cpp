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
	float mVcx, mVcy, mVx, mVy;
    std::vector<ssu::Path> paths;
	Mat3 M = Mat3(1.f);
	Mat3 initM;
	std::vector<Mat3> transforms;

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
			s >> model.Vx >> model.Vy;
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
			paths.push_back(ssu::Path(
				vertices,
				Color{
					static_cast<uint8_t>(r),
					static_cast<uint8_t>(g),
					static_cast<uint8_t>(b),
					255
				},
				thickness
			));
		} else if(cmd == "figure") {
			if(!paths.empty()) {
				paths.clear();
			}
			s >> mVcx >> mVcy >> mVx >> mVy;
			float S = mVx / mVy < 1 ? 2.f / mVy : 2.f / mVx;
			initM = scale(S) * translate(-mVcx, -mVcy);
		} else if(cmd == "saveTransform") {
			model.figures.push_back(ssu::Figure(paths, mVx, mVy, M * initM));
		} else if(cmd == "translate") {
			float Tx, Ty;
			s >> Tx >> Ty;
			M = translate(Tx, Ty) * M;
		} else if(cmd == "scale") {
			float S;
			s >> S;
			M = scale(S) * M;
		} else if(cmd == "rotate") {
			float theta;
			s >> theta;
			M = rotate(theta / 180.f * M_PI) * M;
		} else if(cmd == "saveTransform" || cmd == "pushTransform") {
			transforms.push_back(M);
		} else if(cmd == "popTransform") {
			M = transforms.back();
			transforms.pop_back();
		}
	}
	return model;
}

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
	Wcx = Wx / 2.0f;
	Wcy = Wy / 2.0f;
	frameAspect = Wx / Wy;
}

int main() {
	if (NFD_Init() != NFD_OKAY) {
		std::cerr << "ERROR: can't initialize Native File Dialog" << std::endl;
		return EXIT_FAILURE;
	}

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(600, 600, "Lab cuatro");
	SetTargetFPS(60);

	ssu::Model model;
	Mat3 T = Mat3(1.f);
	Mat3 initT;

	const Padding paddings = { 30.f, 160.f, 20.f, 50.f }; // расстояния от границ окна
	float Wx, Wy, Wcx, Wcy, frameAspect;
	frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);
	
	while (!WindowShouldClose()) {
		if(IsWindowResized()) {
			frame_calc(paddings, Wx, Wy, Wcx, Wcy, frameAspect);
		}

		// Render figures
		BeginDrawing();
		ClearBackground(SKYBLUE);

		DrawRectangleLinesEx({
			paddings.left, // слева
			paddings.top, // сверху
			Wx, // ширина
			Wy // высота
		}, 2.f, BLACK);

		for (const auto &figure : model.figures) {
			Mat3 TM = T * figure.M;
			for (const auto &lines : figure.paths) {
				Vec2 start = normalize(TM * Vec3(lines.vertices[0], 1));
				for (const auto &line : lines.vertices) {
					Vec2 end = normalize(TM * Vec3(line, 1));
					Vec2 old_end = end;
					if(clip(start, end, {paddings.left, paddings.top}, {paddings.left + Wx, paddings.top + Wy})) {
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

		if (GuiButton({static_cast<float>(GetScreenWidth()) - 140, 20, 120, 30}, "OPEN FILE")) {
			nfdchar_t *outPath;
			nfdfilteritem_t filterItem[2]
				= {{"Text files", "txt"}, {"All files", "*"}};
			nfdresult_t result
				= NFD_OpenDialog(&outPath, filterItem, 2, nullptr);
			if (result == NFD_OKAY) {
				model = readFromFile(outPath);
				const float figureAspect = model.Vx / model.Vy;
				Mat3 T1 = translate(-model.Vx / 2, -model.Vy / 2);
				const float S = figureAspect < frameAspect ? Wy / model.Vy
															: Wx / model.Vx;
				Mat3 S1 = scale(S, -S);
				Mat3 T2 = translate(Wx / 2, Wy / 2); // WARN: Миронов походу знаки попутал
				initT = T2 * (S1 * T1);
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
			T = translate(-Wx, -Wy) * T;
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

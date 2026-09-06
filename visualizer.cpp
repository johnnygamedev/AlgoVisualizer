#include "raylib.h"


int main() {
	InitWindow(800, 600, "window");
	SetTargetFPS(240);

	while (!WindowShouldClose()) {

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("raylib #working #beastmode", 100, 250, 40, DARKGRAY);
		EndDrawing();
	}

	
	CloseWindow();

	return 0;
}
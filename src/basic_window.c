#include "raylib.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	600
#define FONT_SIZE	40

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "First Example - Basic Window");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("This is my first window, wow!", 
				140, (SCREEN_HEIGHT / 2) - FONT_SIZE / 2, FONT_SIZE, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}



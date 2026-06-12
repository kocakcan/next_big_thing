#include "raylib.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	450
#define SCROLL_SPEED	4

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Input Mouse Wheel");
	int boxPositionY = SCREEN_HEIGHT / 2;
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		boxPositionY -= (int)(GetMouseWheelMove() * SCROLL_SPEED);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawRectangle(SCREEN_WIDTH / 2 - 40, boxPositionY,
				80, 80, MAROON);
		DrawText("Use mouse wheel to move the cube up and down!",
				10, 10, 20, GRAY);
		DrawText(TextFormat("Box position Y: %03i", boxPositionY),
				10, 40, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

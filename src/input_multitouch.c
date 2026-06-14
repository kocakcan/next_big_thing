#include "raylib.h"

#define MAX_TOUCH_POINTS	10
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		450

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Input Multitouch");
	Vector2 touchPositions[MAX_TOUCH_POINTS] = {0};
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		int tCount = GetTouchPointCount();
		if (tCount > MAX_TOUCH_POINTS)
			tCount = MAX_TOUCH_POINTS;
		for (int i = 0; i < tCount; ++i)
			touchPositions[i] = GetTouchPosition(i);
		BeginDrawing();
		ClearBackground(RAYWHITE);
		for (int i = 0; i < tCount; ++i) {
			if ((touchPositions[i].x > 0) && 
				(touchPositions[i].y > 0)) {
				DrawCircleV(touchPositions[i], 34, ORANGE);
				DrawText(TextFormat("%d", i),
			(int)touchPositions[i].x - 10, 
			(int)touchPositions[i].y - 70, 40, BLACK);
			}
		}
		DrawText("Touch the screen at multiple locations to get"
			" multiple balls", 10, 10, 20, DARKGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}
			

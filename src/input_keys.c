#include "raylib.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	450

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Input Keys");
	Vector2 ballPosition = { (float)SCREEN_WIDTH / 2, 
				 (float)SCREEN_HEIGHT / 2 };
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += 2.0f;
		if (IsKeyDown(KEY_LEFT)) ballPosition.x -= 2.0f;
		if (IsKeyDown(KEY_UP)) ballPosition.y -= 2.0f;
		if (IsKeyDown(KEY_DOWN)) ballPosition.y += 2.0f;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Move the ball with arrow keys", 
				10, 10, 20, DARKGRAY);
		DrawCircleV(ballPosition, 50, MAROON);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

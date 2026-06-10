#include "raylib.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	450
#define RADIUS		50
#define SPEED		2.0f
#define RESET()	\
	do { \
		ballPosition.x = SCREEN_WIDTH / 2.0f; \
		ballPosition.y = SCREEN_HEIGHT / 2.0f; \
	} while (0)	

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Input Keys");
	Vector2 ballPosition = { (float)SCREEN_WIDTH / 2, 
				 (float)SCREEN_HEIGHT / 2 };
	SetTargetFPS(60);
	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_RIGHT)) ballPosition.x += SPEED;
		if (IsKeyDown(KEY_LEFT)) ballPosition.x -= SPEED;
		if (IsKeyDown(KEY_UP)) ballPosition.y -= SPEED;
		if (IsKeyDown(KEY_DOWN)) ballPosition.y += SPEED;
		if (IsKeyPressed(KEY_R)) RESET();

		if ((ballPosition.x + RADIUS < 0 
			|| ballPosition.x - RADIUS > SCREEN_WIDTH) ||
		    (ballPosition.y + RADIUS < 0
		     	|| ballPosition.y - RADIUS > SCREEN_HEIGHT)) {
			RESET();
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Move the ball with arrow keys", 
				10, 10, 20, DARKGRAY);
		DrawText("Press R to reset the position",
				10, 30, 20, DARKGRAY);
		DrawCircleV(ballPosition, RADIUS, MAROON);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

#include "raylib.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	450
#define SPEED		10.0f
#define CIRCLE_RADIUS	32.0f

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Delta Time");
	int currentFPS = 60;
	Vector2 deltaCircle = { 0, (float)SCREEN_HEIGHT / 3.0f };
	Vector2 frameCircle = { 0, (float)SCREEN_HEIGHT * (2.0f / 3.0f) };
	SetTargetFPS(currentFPS);

	while (!WindowShouldClose()) {
		float mouseWheel = GetMouseWheelMove();
		if (mouseWheel != 0) {
			currentFPS += (int)mouseWheel;
			if (currentFPS < 0) currentFPS = 0;
			SetTargetFPS(currentFPS);
		}
		// GetFrameTime() returns the time it took to draw the last
		// frame, in seconds (usually called delta time)

		// Multiply by 6.0 (an arbitrary value) in order to make the
		// speed visually closer to the other circle (at 60 FPS), for
		// comparison
		deltaCircle.x += GetFrameTime() * 6.0f * SPEED;
		frameCircle.x += 0.1f * SPEED;

		// If either circle is off the screen, reset it back to the
		// start
		if (deltaCircle.x > SCREEN_WIDTH) deltaCircle.x = 0;
		if (frameCircle.x > SCREEN_WIDTH) frameCircle.x = 0;

		// Reset both circles positions
		if (IsKeyPressed(KEY_R)) {
			deltaCircle.x = 0;
			frameCircle.x = 0;
		}

		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircleV(deltaCircle, CIRCLE_RADIUS, RED);
		DrawCircleV(frameCircle, CIRCLE_RADIUS, BLUE);

		// Draw the help text
		// Determine what help text to show depending on the current FPS
		// target
		const char *fpsText = 0;
		if (currentFPS <= 0) 
			fpsText = TextFormat("FPS: unlimited (%i)", GetFPS());
		else 
			fpsText = TextFormat("FPS: %i (target: %i)",
					GetFPS(), currentFPS);
		DrawText(fpsText, 10, 10, 20, DARKGRAY);
		DrawText(TextFormat("Frame time: %02.0f ms", GetFrameTime()),
				10, 30, 20, DARKGRAY);
		DrawText("Use the scroll wheel to change the FPS limit, R to reset",
				10, 50, 20, DARKGRAY);
		DrawText("FUNC: x += GetFrameTime() * SPEED",
				10, 90, 20, RED);
		DrawText("FUNC: x += SPEED",
				10, 240, 20, BLUE);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}

#include "raylib.h"

#define MAX_FRAME_SPEED		60
#define MIN_FRAME_SPEED		1
#define FRAME_SPEED_STEP	5
#define SPEED_BARS		(MAX_FRAME_SPEED / FRAME_SPEED_STEP)
#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		450

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Scarfy");
	// textures must be loaded after window initialization (opengl context
	// required)
	Texture2D scarfy = LoadTexture("resources/scarfy.png");
	Vector2 position = { 350.0f, 280.0f };
	Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width / 6, 
					   (float)scarfy.height };
	int currentFrame = 0;
	int framesSpeed = 8;
	float frameTimer = 0.0f;
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		float dt = GetFrameTime();
		frameTimer += dt;
		if (frameTimer >= (1.0f / framesSpeed)) {
			frameTimer = 0.0f;
			currentFrame++;
			if (currentFrame > 5)
				currentFrame = 0;
			frameRec.x = (float)currentFrame * (float)scarfy.width / 6;
		}
		if (IsKeyPressed(KEY_RIGHT))
			framesSpeed += FRAME_SPEED_STEP;
		else if (IsKeyPressed(KEY_LEFT))
			framesSpeed -= FRAME_SPEED_STEP;
		if (framesSpeed > MAX_FRAME_SPEED)
			framesSpeed = MAX_FRAME_SPEED;
		else if (framesSpeed < MIN_FRAME_SPEED) 
			framesSpeed = MIN_FRAME_SPEED;
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawTexture(scarfy, 15, 40, WHITE);
		DrawRectangleLines(15, 40, scarfy.width, scarfy.height, LIME);
		DrawRectangleLines(15 + (int)frameRec.x, 40 + (int)frameRec.y, 
				(int)frameRec.width, (int)frameRec.height, RED);
		DrawText("FRAME SPEED: ", 165, 210, 10, DARKGRAY);
		DrawText(TextFormat("%02i FPS", framesSpeed), 575, 210, 10, DARKGRAY);
		DrawText("PRESS RIGHT/LEFT KEYS to CHANGE SPEED!", 290, 240, 10, DARKGRAY);
		int filledBars = framesSpeed / FRAME_SPEED_STEP;
		for (int i = 0; i < SPEED_BARS; ++i) {
			if (i < filledBars)
				DrawRectangle(250 + 26 * i, 205, 20, 20, RED);
			DrawRectangleLines(250 + 26 * i, 205, 20, 20, MAROON);
		}
		DrawTextureRec(scarfy, frameRec, position, WHITE); /* draw part of the texture */
		EndDrawing();
	}
	UnloadTexture(scarfy);
	CloseWindow();
	return 0;
}


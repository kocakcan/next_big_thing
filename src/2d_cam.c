#include "raylib.h"
#include <math.h>

#define MAX_BUILDINGS	100
#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	450
#define BASE_SPEED	2.0f
#define ROT_FACTOR	2.84f	// how tilting affects speed

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Camera");
	Rectangle player = { 400, 280, 40, 40 };
	Rectangle buildings[MAX_BUILDINGS] = { 0 };
	Color buildColors[MAX_BUILDINGS] = { 0 };
	int spacing = 0;

	for (int i = 0; i < MAX_BUILDINGS; ++i) {
		buildings[i].width = (float)GetRandomValue(50, 200);
		buildings[i].height = (float)GetRandomValue(100, 800);
		buildings[i].y = SCREEN_HEIGHT - 130.0f - buildings[i].height;
		buildings[i].x = -6000.0f + spacing;
		spacing += (int)buildings[i].width;
		buildColors[i] = (Color){
			(unsigned char)GetRandomValue(200, 240),
			(unsigned char)GetRandomValue(200, 240),
			(unsigned char)GetRandomValue(200, 250),
			255
		};
	}
	Camera2D camera = { 0 };
	camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
	camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
	camera.zoom = 1.0f;
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		float speed = 0.0f;
		if (IsKeyDown(KEY_RIGHT)) {
			speed = BASE_SPEED + camera.rotation * ROT_FACTOR;
			// if (speed < 0.2f)
				// speed = 0.2f;
			player.x += speed;
		} else if (IsKeyDown(KEY_LEFT)) {
			speed = BASE_SPEED - camera.rotation * ROT_FACTOR;
			// if (speed < 0.2f)
				// speed = 0.2f;
			player.x -= speed;
		}

		// camera target follows player
		camera.target = (Vector2){ player.x + 20, player.y + 20 };
		if (IsKeyDown(KEY_A)) camera.rotation--;
		else if (IsKeyDown(KEY_S)) camera.rotation++;
		if (camera.rotation > 40) camera.rotation = 40;
		else if (camera.rotation < -40) camera.rotation = -40;
		camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove()
					* 0.1f));
		if (camera.zoom > 3.0f) camera.zoom = 3.0f;
		else if (camera.zoom < 0.1f) camera.zoom = 0.1f;
		if (IsKeyPressed(KEY_R)) {
			camera.zoom = 1.0f;
			camera.rotation = 0.0f;
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
		DrawRectangle(-6000, 320, 13000, 8000, DARKGRAY);
		for (int i = 0; i < MAX_BUILDINGS; ++i)
			DrawRectangleRec(buildings[i], buildColors[i]);
		DrawRectangleRec(player, RED);
		DrawLine((int)camera.target.x, -SCREEN_HEIGHT * 10, (int)camera.target.x,
				SCREEN_HEIGHT * 10, GREEN);
		DrawLine(-SCREEN_WIDTH * 10, (int)camera.target.y, SCREEN_WIDTH * 10, 
				(int)camera.target.y, GREEN);
		EndMode2D();
		DrawText("SCREEN AREA", 640, 10, 20, RED);
		DrawRectangle(0, 0, SCREEN_WIDTH, 5, RED);
		DrawRectangle(0, 5, 5, SCREEN_HEIGHT - 10, RED);
		DrawRectangle(SCREEN_WIDTH - 5, 5, 5, SCREEN_HEIGHT - 10, RED);
		DrawRectangle(0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5, RED);
		DrawRectangle(10, 10, 250, 113, Fade(SKYBLUE, 0.5f));
		DrawRectangleLines(10, 10, 250, 113, BLUE);
		DrawText("Free 2D camera controls:", 20, 20, 10, BLACK);
		DrawText("- Right/Left to move player", 40, 40, 10, DARKGRAY);
		DrawText("- Mouse Wheel to Zoom in-out", 40, 60, 10, DARKGRAY);
		DrawText("- A / S to Rotate", 40, 80, 10, DARKGRAY);
		DrawText("- R to reset Zoom and Rotation", 40, 100, 10, DARKGRAY);
		DrawText(TextFormat("Current speed: %.2f p/s", speed), 640, 30, 10, RED);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}



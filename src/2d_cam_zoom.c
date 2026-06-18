#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#define SCREEN_WIDTH	800
#define SCREEN_HEIGHT	450

int main(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "2D Camera Mouse Zoom");
	Camera2D camera = { 0 };
	camera.zoom = 1.0f;
	int zoomMode = 0;	
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_ONE))
			zoomMode = 0;	// Mouse Wheel
		else if (IsKeyPressed(KEY_TWO))
			zoomMode = 1;	// Mouse Move
		// Translate based on mouse right click
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / camera.zoom);
			camera.target = Vector2Add(camera.target, delta);
		}
		if (zoomMode == 0) {
			// Zoom based on mouse wheel
			float wheel = GetMouseWheelMove();
			if (wheel != 0) {
				// Get the world point that is under the mouse
				Vector2 mouseWorldPos = 
					GetScreenToWorld2D(GetMousePosition(),
							camera);
				// Set the offset to where the mouse is
				camera.offset = GetMousePosition();
				// Set the target to match, so that the camera 
				// maps the world space point under the cursor 
				// at any zoom
				camera.target = mouseWorldPos;
				// Zoom increment
				// Uses log scaling to provide consistent zoom
				// speed
				float scale = 0.2f * wheel;
				camera.zoom = Clamp(expf(logf(
							camera.zoom) + scale)
						, 0.125f, 64.0f);
			}
		} else {
			// Zoom based on mouse right click
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
				Vector2 mouseWorldPos =
					GetScreenToWorld2D(GetMousePosition(),
							camera);
				// Set the offset to where the mouse is
				camera.offset = GetMousePosition();
				camera.target = mouseWorldPos;
			}

			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				// Zoom increment
				// Uses log scaling to provide consistent zoom
				// speed
				float deltaX = GetMouseDelta().x;
				float scale = 0.005f * deltaX;
				camera.zoom = Clamp(expf(logf
							(camera.zoom)+ scale)
						, 0.125f, 64.0f);
			}
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		BeginMode2D(camera);
		// Draw the 3D grid, rotated 90 degrees and centered around 0,0
		// just so we have something in the XY plane
		rlPushMatrix();
		rlTranslatef(0, 25 * 50, 0);
		rlRotatef(90, 1, 0, 0);
		DrawGrid(100, 50);
		rlPopMatrix();
		// Draw a reference circle
		DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 
				50, MAROON);
		EndMode2D();
		// Draw mouse reference
		DrawCircleV(GetMousePosition(), 4, DARKGRAY);
		DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(),
					GetMouseY()),
			Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }),
			20, 2, BLACK);
		DrawText("[1][2] Select mouse zoom mode (Wheel or Move)", 20, 20, 20, 
				DARKGRAY);
		if (zoomMode == 0)
			DrawText("Mouse left button drag to move, mouse wheel to zoom", 
					20, 50, 20, DARKGRAY);
		else
			DrawText("Mouse left button drag to move, mouse press and move to zoom",
					20, 50, 20, DARKGRAY);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}



#include "raylib.h"

#define SCREEN_HEIGHT	800
#define SCREEN_WEIGHT	600

int main(void) {
	InitWindow(SCREEN_HEIGHT, SCREEN_WEIGHT, "Practice");

	while (!WindowShouldClose()) {
		ClearBackground(RAYWHITE);
		BeginDrawing();
		// DrawText("I'm drawing some text", 100, 100, 20, BLACK);
		for (int i = 0; i < 100; ++i)
			for (int j = 0; j < 100; ++j)
				DrawPixel(i, j, BLACK);
		EndDrawing();
	}
	CloseWindow();
	return 0;
}


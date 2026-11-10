#include "raylib.h"

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0

#define GAME_TITLE "Elude"

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
#include "raylib.h"

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0

#define GAME_TITLE "Elude"

#define START_BUTTON_WIDTH 200
#define START_BUTTON_HEIGHT 100

#define START_TEXT "Start"

typedef enum game_state {
    MENU,
    INGAME,
} game_state;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    game_state current_state = MENU;

    Rectangle start_button = {
        SCREEN_WIDTH / 2 - 100,
        SCREEN_HEIGHT / 2 + 100,
        START_BUTTON_WIDTH,
        START_BUTTON_HEIGHT,
    };
    Color start_button_color = DARKGRAY;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (CheckCollisionPointRec(GetMousePosition(), start_button)) {
            start_button_color = LIGHTGRAY;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                current_state = INGAME;
            }
        } else {
            start_button_color = DARKGRAY;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        if (current_state == MENU) {
            DrawText(GAME_TITLE, SCREEN_WIDTH / 2 - 120,
                     SCREEN_HEIGHT / 2 - 100, 100, BLACK);

            DrawRectangleRec(start_button, start_button_color);

            DrawText(START_TEXT, start_button.x + 25, start_button.y + 25, 50,
                     BLACK);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
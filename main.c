#include "raylib.h"

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0

#define GAME_TITLE "Elude"

#define START_BUTTON_WIDTH 200
#define START_BUTTON_HEIGHT 100

typedef enum game_state {
    MENU,
    INGAME,
} game_state;

bool start_screen(void);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(60);

    game_state current_state = MENU;

    while (!WindowShouldClose()) {
        ClearBackground(WHITE);

        BeginDrawing();

        if (current_state == MENU) {
            if (!start_screen()) {
                current_state = INGAME;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

Color rectangle_color = DARKGRAY;
bool start_screen(void) {
    DrawText(GAME_TITLE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 100, BLACK);

    Rectangle start_button = {
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2 + 100,
        START_BUTTON_WIDTH,
        START_BUTTON_HEIGHT,
    };

    DrawRectangleRec(start_button, rectangle_color);

    if (CheckCollisionPointRec(GetMousePosition(), start_button)) {
        rectangle_color = LIGHTGRAY;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            return false;
        }
    }

    return true;
}
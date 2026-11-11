#include "raylib.h"
#include <stdlib.h>

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0

#define GAME_TITLE "Elude"

#define START_BUTTON_WIDTH 200
#define START_BUTTON_HEIGHT 100

#define START_TEXT "Start"

#define PLAYER_STARTING_POS_X 600
#define PLAYER_STARTING_POS_Y 600

#define LEVELS_STARTING_Y -750

#define BASE_LEVEL 650

typedef enum game_state {
    MENU,
    INGAME,
    DEATH,
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

    Rectangle player = {
        PLAYER_STARTING_POS_X,
        PLAYER_STARTING_POS_Y,
        20,
        50,
    };

    Rectangle platform = {
        0,
        LEVELS_STARTING_Y,
        1150,
        100,
    };

    Rectangle base_level = {0, BASE_LEVEL, 1280, 200};

    bool randomize_once = true;

    int count_down = 500;

    int score = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (current_state == MENU) {
            if (CheckCollisionPointRec(GetMousePosition(), start_button)) {
                start_button_color = LIGHTGRAY;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    current_state = INGAME;
                }
            } else {
                start_button_color = DARKGRAY;
            }
        } else if (current_state == INGAME) {
            count_down = 500;
            if (IsKeyDown(KEY_A)) {
                player.x -= 5;
            }
            if (IsKeyDown(KEY_D)) {
                player.x += 5;
            }

            platform.y += 5;
            if (CheckCollisionRecs(platform, base_level)) {
                platform.y = LEVELS_STARTING_Y;
                platform.x = rand() % ((int)SCREEN_WIDTH + 1);
            }
            if (CheckCollisionRecs(platform, player)) {
                current_state = DEATH;
            }

            score++;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        if (current_state == MENU) {
            DrawText(GAME_TITLE, SCREEN_WIDTH / 2 - 120,
                     SCREEN_HEIGHT / 2 - 100, 100, BLACK);

            DrawRectangleRec(start_button, start_button_color);

            DrawText(START_TEXT, start_button.x + 25, start_button.y + 25, 50,
                     BLACK);
        } else if (current_state == INGAME) {
            DrawText(TextFormat("%d", score), SCREEN_WIDTH - 50, 20, 25, BLACK);
            DrawRectangleRec(base_level, BLACK);
            DrawRectangleRec(player, BLUE);
            DrawRectangleRec(platform, RED);
        } else {
            DrawText("YOU DIED!", SCREEN_WIDTH / 2 - 150,
                     SCREEN_HEIGHT / 2 + 100, 100, BLACK);

            DrawText(TextFormat("Your Score: %d", score),
                     SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 80, 50, BLACK);

            count_down -= 1;

            if (count_down <= 0) {
                current_state = MENU;
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
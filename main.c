#include "raylib.h"

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0

#define GAME_TITLE "Elude"

#define START_BUTTON_WIDTH 200
#define START_BUTTON_HEIGHT 100

#define START_TEXT "Start"

#define PLAYER_HEALTH 100
#define CURRENT_SCORE 0
#define PLAYER_STARTING_POS_X 600
#define PLAYER_STARTING_POS_Y 680

typedef enum game_state {
    MENU,
    INGAME,
    DEATH,
} game_state;

typedef struct player {
    int health;
    int score;
    Texture2D texture;
    int pos_x;
    const int pos_y;
} player;

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

    player player = {
        PLAYER_HEALTH,
        CURRENT_SCORE,
        LoadTexture("assets/skeleton.png"),
        PLAYER_STARTING_POS_X,
        PLAYER_STARTING_POS_Y,
    };

    Rectangle player_placeholder = {
        player.pos_x,
        player.pos_y,
        20,
        50,
    };

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
            if (IsKeyDown(KEY_A)) {
                // player.pos_x -= 10;
                player_placeholder.x -= 5;
            }
            if (IsKeyDown(KEY_D)) {
                // player.pos_x += 10;
                player_placeholder.x += 5;
            }
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
            // DrawTexture(player.texture, player.pos_x, player.pos_y, WHITE);
            DrawRectangleRec(player_placeholder, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
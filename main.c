#include "raylib.h"

#define SCREEN_WIDTH 1280.0
#define SCREEN_HEIGHT 720.0

#define MAX_INPUT_CHARS 9

typedef enum screen_state {
    MENU,
    INGAME,
} screen_state;

typedef struct player {
    int health;
    char *name;
    char *skin_texture;
} player;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Elude");

    // ask user to enter name. for now use default name

    int player_health = 100;
    char *player_name = "Skeletor";
    char *player_texture = "assets/skeleton.png";
    player player = {player_health, player_name, player_texture};
    Texture2D player_sprite = LoadTexture(player_texture);

    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letter_count = 0;
    Rectangle text_box = {SCREEN_WIDTH / 2.0f - 110, SCREEN_HEIGHT / 2.0f - 100,
                          225, 50};
    bool mouse_on_text = false;
    int frames_counter = 0;
    screen_state screen_state = MENU;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        if (CheckCollisionPointRec(GetMousePosition(), text_box)) {
            mouse_on_text = true;
        } else {
            mouse_on_text = false;
        }

        if (mouse_on_text) {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            int key = GetCharPressed();

            while (key > 0) {
                if ((key >= 32) && (key <= 125) &&
                    (letter_count < MAX_INPUT_CHARS)) {
                    name[letter_count] = (char)key;
                    name[letter_count + 1] = '\0';
                    letter_count++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letter_count--;
                if (letter_count < 0) {
                    letter_count = 0;
                }
                name[letter_count] = '\0';
            }
        } else {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        if (mouse_on_text) {
            frames_counter++;
        } else {
            frames_counter = 0;
        }

        BeginDrawing();

        ClearBackground(WHITE);

        if (screen_state == MENU) {
            DrawRectangleRec(text_box, LIGHTGRAY);
            if (mouse_on_text) {
                DrawRectangleLines((int)text_box.x, (int)text_box.y,
                                   (int)text_box.width, (int)text_box.height,
                                   RED);
            } else {
                DrawRectangleLines((int)text_box.x, (int)text_box.y,
                                   (int)text_box.width, (int)text_box.height,
                                   DARKGRAY);
            }

            DrawText(name, (int)text_box.x + 5, (int)text_box.y + 8, 40,
                     MAROON);

            DrawText(
                TextFormat("NAME LENGTH: %i/%i", letter_count, MAX_INPUT_CHARS),
                SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2, 20, DARKGRAY);

            if (mouse_on_text) {
                if (letter_count < MAX_INPUT_CHARS) {
                    if (((frames_counter / 20) % 2) == 0) {
                        DrawText("_",
                                 (int)text_box.x + 8 + MeasureText(name, 40),
                                 (int)text_box.y + 12, 40, MAROON);
                    }
                } else {
                    DrawText("NAME TOO LONG!", 230, 300, 20, GRAY);
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
#include "draw.h"
#include "data.h"
#include "raylib.h"

void draw_board(Texture2D *board) { DrawTexture(*board, 32, 48, WHITE); }

void draw_ui(GameState *state) { DrawText("Score: ", 10, 10, 20, GREEN); }

void draw_snake(Texture2D *body, Parent *parent) {
  DrawTexturePro(*body, (Rectangle){.x = 0, .y = 0, .width = 32, .height = 32},
                 (Rectangle){.x = parent->head->x * 32 + 48,
                             .y = parent->head->y * 32 + 64,
                             .width = 32,
                             .height = 32},
                 (Vector2){.x = 16, .y = 16}, 0.0, WHITE);
  if (parent->length == 2) {
    DrawTexturePro(*body,
                   (Rectangle){.x = 96, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = parent->tail->x * 32 + 48,
                               .y = parent->tail->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 0.0, WHITE);
  } else if (parent->length > 2) {
    Node *current_node = parent->head->next;
    // Body sprites
    while (current_node->next != NULL) {
      DrawTexturePro(*body,
                     (Rectangle){.x = 128, .y = 0, .width = 32, .height = 32},
                     (Rectangle){.x = current_node->x * 32 + 48,
                                 .y = current_node->y * 32 + 64,
                                 .width = 32,
                                 .height = 32},
                     (Vector2){.x = 16, .y = 16}, 0.0, WHITE);
      current_node = current_node->next;
    }
    // Tail sprite
    DrawTexturePro(*body,
                   (Rectangle){.x = 96, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = parent->tail->x * 32 + 48,
                               .y = parent->tail->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 0.0, WHITE);
  }
}

void draw_food(Texture2D *food, GameState *state) {
  DrawTexture(*food, state->food->x * 32 + 32, state->food->y * 32 + 48, WHITE);
}

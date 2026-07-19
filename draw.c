#include "draw.h"
#include "data.h"
#include "raylib.h"
#include "string.h"

void draw_board(Texture2D *board) { DrawTexture(*board, 32, 48, WHITE); }

void draw_ui(GameState *state) {
  char score_text[12] = "Score: ";
  char score[4];
  snprintf(score, sizeof(score), "%d", state->score);
  strcat(score_text, score);
  DrawText(score_text, 10, 10, 20, GREEN);
}

float get_head_rot(GameState *state) {
  switch (state->prev_dir) {
  case UP:
    return 0.0;
    break;
  case RIGHT:
    return 90.0;
    break;
  case DOWN:
    return 180.0;
    break;
  case LEFT:
    return 270.0;
    break;
  default:
    break;
  }
}

float get_tail_rot(Parent *parent) {
  Node *t = parent->tail;

  if (t->prev->x < t->x) {
    return 270.0;
  } else if (t->prev->x > t->x) {
    return 90.0;
  } else if (t->prev->y < t->y) {
    return 0.0;
  } else {
    return 180.0;
  }
}

void draw_part(Texture2D *body, short offset, short x, short y, float rot) {
  DrawTexturePro(
      *body, (Rectangle){.x = offset * 32, .y = 0, .width = 32, .height = 32},
      (Rectangle){
          .x = x * 32 + 48, .y = y * 32 + 64, .width = 32, .height = 32},
      (Vector2){16, 16}, rot, WHITE);
}

void draw_snake(Texture2D *body, Parent *parent, GameState *state) {
  // Draw head
  float head_rot = get_head_rot(state);
  DrawTexturePro(*body, (Rectangle){.x = 0, .y = 0, .width = 32, .height = 32},
                 (Rectangle){.x = parent->head->x * 32 + 48,
                             .y = parent->head->y * 32 + 64,
                             .width = 32,
                             .height = 32},
                 (Vector2){.x = 16, .y = 16}, head_rot, WHITE);
  if (parent->length == 2) {
    float tail_rot = get_tail_rot(parent);
    DrawTexturePro(*body,
                   (Rectangle){.x = 96, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = parent->tail->x * 32 + 48,
                               .y = parent->tail->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, tail_rot, WHITE);
  } else if (parent->length > 2) {
    Node *current_node = parent->head->next;
    // Body sprites
    while (current_node->next != NULL) {
      Node *p = current_node->prev;
      Node *n = current_node->next;
      // L sprites, horizontal, vertical
      if ((p->y < current_node->y && n->y == current_node->y) &&
              (p->x == current_node->x && n->x > current_node->x) ||
          (n->y < current_node->y && p->y == current_node->y) &&
              (n->x == current_node->x && p->x > current_node->x)) {
        draw_part(body, 2, current_node->x, current_node->y, 0);
      } else if ((p->y == current_node->y && n->y > current_node->y) &&
                     (p->x > current_node->x && n->x == current_node->x) ||
                 (n->y == current_node->y && p->y > current_node->y) &&
                     (n->x > current_node->x && p->x == current_node->x)) {
        draw_part(body, 2, current_node->x, current_node->y, 90);
      } else if ((p->y > current_node->y && n->y == current_node->y) &&
                     (p->x == current_node->x && n->x < current_node->x) ||
                 (n->y > current_node->y && p->y == current_node->y) &&
                     (n->x == current_node->x && p->x < current_node->x)) {

        draw_part(body, 2, current_node->x, current_node->y, 180);
      } else if ((p->y < current_node->y && n->y == current_node->y) &&
                     (p->x == current_node->x && n->x < current_node->x) ||
                 (n->y < current_node->y && p->y == current_node->y) &&
                     (n->x == current_node->x && p->x < current_node->x)) {

        draw_part(body, 2, current_node->x, current_node->y, 270);
      } else if ((p->y == current_node->y && n->y == current_node->y) &&
                     (p->x > current_node->x && n->x < current_node->x) ||
                 (n->y == current_node->y && p->y == current_node->y) &&
                     (n->x > current_node->x && p->x < current_node->x)) {

        draw_part(body, 1, current_node->x, current_node->y, 90);
      } else if ((p->y > current_node->y && n->y < current_node->y) &&
                     (p->x == current_node->x && n->x == current_node->x) ||
                 (n->y > current_node->y && p->y < current_node->y) &&
                     (n->x == current_node->x && p->x == current_node->x)) {
        draw_part(body, 1, current_node->x, current_node->y, 0);
      }
      current_node = current_node->next;
    }
    // Tail sprite
    float tail_rot = get_tail_rot(parent);
    DrawTexturePro(*body,
                   (Rectangle){.x = 96, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = parent->tail->x * 32 + 48,
                               .y = parent->tail->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, tail_rot, WHITE);
  }
}

void draw_food(Texture2D *food, GameState *state) {
  DrawTexture(*food, state->food->x * 32 + 32, state->food->y * 32 + 48, WHITE);
}

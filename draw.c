#include "draw.h"
#include "raylib.h"
#include "snake_data.h"

void draw_neighbors(Coord *node, Texture2D *sprite) {
  Coord *p = node->prev;
  Coord *n = node->next;

  if ((node->x == n->x && node->y > n->y) &&
          (node->x < p->x && node->y == p->y) ||
      (node->x == p->x && node->y > p->y) &&
          (node->x < n->x && node->y == n->y)) {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 64, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = node->x * 32 + 48,
                               .y = node->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 0.0f, WHITE);
  } else if ((node->x == n->x && node->y < n->y) &&
                 (node->x < p->x && node->y == p->y) ||
             (node->x == p->x && node->y < p->y) &&
                 (node->x < n->x && node->y == n->y)) {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 64, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = node->x * 32 + 48,
                               .y = node->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 90.0f, WHITE);
  } else if ((node->x == p->x && node->y < p->y) &&
                 (node->x > n->x && node->y == n->y) ||
             (node->x == n->x && node->y < n->y) &&
                 (node->x > p->x && node->y == p->y)) {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 64, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = node->x * 32 + 48,
                               .y = node->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 180.0f, WHITE);
  } else if ((node->x == p->x && node->y > p->y) &&
                 (node->x > n->x && node->y == n->y) ||
             (node->x == n->x && node->y > n->y) &&
                 (node->x > p->x && node->y == p->y)) {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 64, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = node->x * 32 + 48,
                               .y = node->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 270.0f, WHITE);
  } else if ((node->x > p->x && node->y == p->y) &&
                 (node->x < n->x && node->y == n->y) ||
             (node->x > n->x && node->y == n->y) &&
                 (node->x < p->x && node->y == p->y)) {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 32, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = node->x * 32 + 48,
                               .y = node->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 90.0f, WHITE);
  } else {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 32, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = node->x * 32 + 48,
                               .y = node->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, 0.0f, WHITE);
  }
}

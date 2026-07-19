#include "raylib.h"
#include "snake_data.h"
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"

// gameboard[y][x]

void init_game_board(char game_board[9][18]) {
  for (size_t i = 0; i < 9; i++) {
    for (size_t j = 0; j < 18; j++) {
      game_board[i][j] = 0;
      // printf("%lu %lu\n", i, j);
    }
  }
  // game_board[4][5] = 1;
}

void update_player(player_t *player) {
  Coord *new_head = malloc(sizeof(Coord));
  switch (player->dir) {
  case U:
    player->prev_dir = U;
    new_head->y = player->head->y - 1;
    new_head->x = player->head->x;
    break;
  case L:
    player->prev_dir = L;
    new_head->x = player->head->x - 1;
    new_head->y = player->head->y;
    break;
  case R:
    player->prev_dir = R;
    new_head->x = player->head->x + 1;
    new_head->y = player->head->y;
    break;
  case D:
    player->prev_dir = D;
    new_head->y = player->head->y + 1;
    new_head->x = player->head->x;
    break;
  default:
    break;
  }
  if (player->length == 1) {
    free(player->head);
    new_head->next = NULL;
    new_head->prev = NULL;
    player->head = new_head;
    printf("new_head: %hd %hd \n", player->head->y, player->head->x);
  }
}

void init_player(player_t *player) {
  Coord *head = malloc(sizeof(Coord));
  head->x = 5;
  head->y = 4;
  head->next = NULL;
  head->prev = NULL;
  player->head = head;
  player->dir = U;
  player->prev_dir = D;
  player->length = 1;
}

void update_board(player_t *player, char game_board[9][18]) {
  if (player->head->next == NULL) {
    return;
  }
  Coord *current_node;
  current_node = player->head->next;
  while (current_node != NULL) {
    game_board[current_node->y][current_node->x] = 1;
    current_node = current_node->next;
  }
}

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
  }
}

void draw_player(player_t *player, Texture2D *sprite) {
  Coord *current_node;
  current_node = player->head;
  float rot;
  switch (player->dir) {
  case U:
    rot = 0;
    break;
  case L:
    rot = 270;
    break;
  case R:
    rot = 90;
    break;
  case D:
    rot = 180;
    break;
  default:
    break;
  }
  Vector2 draw_coord;
  draw_coord.x = current_node->x;
  draw_coord.y = current_node->y;
  DrawTexturePro(
      *sprite,
      (Rectangle){
          .x = 0.0f, .y = 0.0f, .width = (float)32, .height = (float)32},
      (Rectangle){.x = current_node->x * 32 + 48,
                  .y = current_node->y * 32 + 64,
                  .width = 32,
                  .height = 32},
      (Vector2){.x = 16, .y = 16}, rot, WHITE);
  if (player->length > 2) {
    while (current_node->next != NULL) {
      draw_neighbors(current_node, sprite);
      current_node = current_node->next;
    }
  } else if (player->length == 2) {
    DrawTexturePro(*sprite,
                   (Rectangle){.x = 96, .y = 0, .width = 32, .height = 32},
                   (Rectangle){.x = current_node->next->x * 32 + 48,
                               .y = current_node->next->y * 32 + 64,
                               .width = 32,
                               .height = 32},
                   (Vector2){.x = 16, .y = 16}, rot, WHITE);
  }
}

int main() {
  int screen_width = 640;
  int screen_height = 360;
  InitWindow(screen_width, screen_height, "PREALPHA SNAKE");

  GameState game_state = MENU;
  float frame_time = 0.0f;
  SetTargetFPS(60);
  player_t *Player = malloc(sizeof(player_t));
  Food food;
  food.value = 1;
  food.x = GetRandomValue(0, 17);
  food.y = GetRandomValue(0, 8);
  printf("food loc: %hd %hd\n ", food.y, food.x);
  init_player(Player);

  char game_board[9][18];
  int score = 0;

  Texture2D game_board_texture = LoadTexture("assets/game_board.png");
  Texture2D snake_head = LoadTexture("assets/snake-head.png");
  Texture2D snake_boi = LoadTexture("assets/snake_boi");
  Texture2D food_texture = LoadTexture("assets/food.png");

  while (!WindowShouldClose()) {
    int mouse_x = GetMouseX();
    int mouse_y = GetMouseY();
    char mouse_text[10];
    char player_pos[10];
    snprintf(mouse_text, sizeof(mouse_text), "%d %d", mouse_x, mouse_y);
    snprintf(player_pos, sizeof(player_pos), "%hd %hd", Player->head->y,
             Player->head->x);
    switch (game_state) {
    case MENU:
      if (IsKeyReleased(KEY_P)) {
        game_state = PLAY;
        printf("PLAYING\n");
        init_game_board(game_board);
        game_board[food.y][food.x] = 2;
      }
      break;
    case PLAY:
      // printf("%02.02f\n", frame_time);
      // if frame_time = 60:
      // set to 0 and update position
      // handle position conditions and kill player if invalid position
      // read input and set direction accordingly
      // frame_time++
      if (frame_time >= 1.0f) {
        frame_time = 0;
        update_player(Player);
        update_board(Player, game_board);
        if (game_board[Player->head->y][Player->head->x] == 1) {
          game_state = DEAD;
        } else if (game_board[Player->head->y][Player->head->x] == 2) {
          score += food.value;
          food.x = GetRandomValue(0, 17);
          food.y = GetRandomValue(0, 8);
          printf("food loc: %hd %hd\n ", food.y, food.x);
          game_board[Player->head->y][Player->head->x] = 0;
          game_board[food.y][food.x] = 2;
          printf("%d\n", score);
        }
      }
      if (IsKeyPressed(KEY_UP)) {
        if (Player->prev_dir != D) {
          Player->dir = U;
        }
      }
      if (IsKeyPressed(KEY_LEFT)) {
        if (Player->prev_dir != R) {
          Player->dir = L;
        }
      }
      if (IsKeyPressed(KEY_RIGHT)) {
        if (Player->prev_dir != L) {
          Player->dir = R;
        }
      }
      if (IsKeyPressed(KEY_DOWN)) {
        if (Player->prev_dir != U) {
          Player->dir = D;
        }
      }
      frame_time += GetFrameTime();
      break;
    case DEAD:
      break;
    default:
      break;
    }

    BeginDrawing();
    switch (game_state) {
    case MENU:
      ClearBackground(GRAY);
      DrawText("Pressssss P to play", 100, 100, 32, WHITE);
      break;
    case PLAY:
      ClearBackground(WHITE);
      DrawTexture(game_board_texture, 33, 49, WHITE);
      draw_player(Player, &snake_head);
      DrawTexturePro(food_texture,
                     (Rectangle){.x = 0, .y = 0, .width = 32, .height = 32},
                     (Rectangle){.x = food.x * 32 + 48,
                                 .y = food.y * 32 + 64,
                                 .width = 32,
                                 .height = 32},
                     (Vector2){.x = 16, .y = 16}, 0, WHITE);
      DrawText(mouse_text, 400, 300, 32, RED);
      DrawText(player_pos, 300, 300, 32, RED);
      break;
    case DEAD:
      ClearBackground(RED);
      DrawText("YOUR DEAD LOL", 200, 200, 100, WHITE);
      break;
    default:
      break;
    }
    EndDrawing();
  }

  CloseWindow();

  return 0;
}

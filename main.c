#include "data.h"
#include "draw.h"
#include "engine.h"
#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

// gameboard[y][x]

int main() {
  int screen_width = 640;
  int screen_height = 360;

  int board_y = 9;
  int board_x = 18;

  InitWindow(screen_width, screen_height, "PREALPHA SNAKE");
  SetTargetFPS(60);

  GameState *state = (GameState *)MemAlloc(sizeof(GameState));
  state->food = MemAlloc(sizeof(Node));
  state->mode = MENU;
  state->score = 0;
  state->move_dir = RIGHT;

  Parent *player = (Parent *)MemAlloc(sizeof(Parent));
  init_player(player, state);

  short **board = init_board(board_y, board_x);

  gen_food(state, board);
  float frame_time = 0;

  Texture2D game_board_texture = LoadTexture("assets/game_board.png");
  Texture2D snake_head = LoadTexture("assets/snake-head.png");
  Texture2D snake_boi = LoadTexture("assets/snake-boi.png");
  Texture2D food_texture = LoadTexture("assets/food.png");

  while (!WindowShouldClose()) {
    // update
    switch (state->mode) {
    case MENU:
      if (IsKeyPressed(KEY_SPACE)) {
        state->mode = PLAY;
      }
      break;
    case PLAY:
      read_input(state);
      frame_time += GetFrameTime();
      if (frame_time >= 0.5f) {
        printf("tick\n");
        tick_update(player, state, board);
        frame_time = 0.0;
      }
      break;
    case KILL:
      break;
    default:
      break;
    }
    // draw
    BeginDrawing();
    switch (state->mode) {
    case MENU:
      ClearBackground(SKYBLUE);
      break;
    case PLAY:
      ClearBackground(BLACK);
      draw_board(&game_board_texture);
      draw_ui(state);
      draw_snake(&snake_boi, player);
      draw_food(&food_texture, state);
      break;
    case KILL:
      ClearBackground(RED);
      DrawText("HAHA", 200, 200, 100, WHITE);
      break;
    }

    EndDrawing();
  }
  CloseWindow();

  return 0;
}

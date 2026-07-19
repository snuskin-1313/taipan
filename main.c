#include "data.h"
#include "draw.h"
#include "engine.h"
#include "raylib.h"
#include "stdio.h"
#include <string.h>

// gameboard[y][x]

int main() {
  int screen_width = 640;
  int screen_height = 360;

  int board_y = 9;
  int board_x = 18;

  InitWindow(screen_width, screen_height, "PREALPHA SNAKE");
  InitAudioDevice();
  SetTargetFPS(60);

  GameState *state = (GameState *)MemAlloc(sizeof(GameState));
  state->food = MemAlloc(sizeof(Node));
  state->mode = MENU;
  state->score = 0;
  state->move_dir = RIGHT;
  state->prev_dir = RIGHT;
  state->sounds[0] = LoadSound("assets/pickup.wav");
  state->sounds[1] = LoadSound("assets/death.wav");

  bool is_dead = false;

  Parent *player = (Parent *)MemAlloc(sizeof(Parent));
  init_player(player, state);

  short **board = init_board(board_y, board_x);

  gen_food(state, board);
  float frame_time = 0;

  Texture2D game_board_texture = LoadTexture("assets/game_board.png");
  Texture2D snake_head = LoadTexture("assets/snake-head.png");
  Texture2D snake_boi = LoadTexture("assets/snake-boi.png");
  Texture2D food_texture = LoadTexture("assets/food.png");

  Sound death = LoadSound("assets/synth.wav");
  Sound pickup = LoadSound("assets/pickup.wav");

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
      if (frame_time >= 0.3f) {
        printf("tick\n");
        tick_update(player, state, board);
        frame_time = 0.0;
      }
      break;
    case KILL:
      if (is_dead == false) {
        is_dead = true;
        PlaySound(death);
      }
      break;
    default:
      break;
    }
    // draw
    BeginDrawing();
    switch (state->mode) {
    case MENU:
      ClearBackground(GRAY);
      DrawText("snake game", 100, 100, 80, WHITE);
      DrawText("press space to play", 100, 200, 30, WHITE);
      break;
    case PLAY:
      ClearBackground(BLACK);
      draw_board(&game_board_texture);
      draw_ui(state);
      draw_snake(&snake_boi, player, state);
      draw_food(&food_texture, state);
      break;
    case KILL:
      ClearBackground(RED);
      DrawText("YOU ARE DEAD", 50, 50, 70, WHITE);
      char score_text[12] = "Score: ";
      char score[4];
      snprintf(score, sizeof(score), "%d", state->score);
      strcat(score_text, score);
      DrawText(score_text, 200, 200, 40, WHITE);
      DrawText("press esc to quit", 250, 300, 40, WHITE);
      break;
    }

    EndDrawing();
  }
  CloseAudioDevice();
  CloseWindow();

  return 0;
}

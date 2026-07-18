#pragma once
#include "raylib.h"

typedef enum GameState { MENU, PLAY, DEAD } GameState;
typedef enum dir { U = 1, L = 2, R = 3, D = 4 } dir;

typedef struct Coord {
  short x;
  short y;
  struct Coord *next;
  struct Coord *prev;
} Coord;

typedef struct {
  struct Coord *head;
  dir dir;
  enum dir prev_dir;
  int length;
} player_t;

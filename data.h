#pragma once

#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

typedef enum { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3 } dir;

typedef enum { MENU = 0, PLAY = 1, KILL = 2 } GameMode;

typedef struct Node {
  short x;
  short y;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  struct Node *head;
  struct Node *tail;
  short length;
} Parent;

typedef struct {
  GameMode mode;
  int score;
  Node *food;
  dir move_dir;
  dir prev_dir;
  Sound sounds[2];
} GameState;

Node *make_node(short x, short y);
void del_node(Node *node);
short **init_board(int y, int x);

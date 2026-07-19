#include "data.h"
#include "raylib.h"

Node *make_node(short x, short y) {
  Node *new_node = (Node *)MemAlloc(sizeof(Node));
  new_node->x = x;
  new_node->y = y;

  return new_node;
}

void del_node(Node *node) { MemFree(node); }

// Initialize the board to 0
short **init_board(int y, int x) {
  short **board = (short **)MemAlloc(sizeof(short *) * y);
  for (int i = 0; i < y; i++) {
    board[i] = (short *)MemAlloc(sizeof(short) * x);
  }

  for (int i = 0; i < y; i++) {
    for (int j = 0; j < x; j++) {
      board[i][j] = (short)0;
    }
  }
  return board;
}

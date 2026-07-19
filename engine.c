#include "engine.h"
#include "data.h"
#include "raylib.h"
#include "stdio.h"

void read_input(GameState *state) {
  if (IsKeyReleased(KEY_UP) && state->prev_dir != DOWN) {
    printf("pressed UP\n");
    state->move_dir = UP;
  } else if (IsKeyReleased(KEY_LEFT) && state->prev_dir != RIGHT) {
    printf("pressed LEFT\n");
    state->move_dir = LEFT;
  } else if (IsKeyReleased(KEY_RIGHT) && state->prev_dir != LEFT) {
    printf("pressed RIGHT\n");
    state->move_dir = RIGHT;
  } else if (IsKeyReleased(KEY_DOWN) && state->prev_dir != UP) {
    printf("pressed DOWN\n");
    state->move_dir = DOWN;
  }
};

// Return a new node to be assigned to parent->head
Node *make_head(Parent *parent, dir dir) {
  printf("make_head()\n");
  Node *new = (Node *)MemAlloc(sizeof(Node));
  switch (dir) {
  case UP:
    new->x = parent->head->x;
    new->y = parent->head->y - 1;
    break;
  case RIGHT:
    new->x = parent->head->x + 1;
    new->y = parent->head->y;
    break;
  case DOWN:
    new->x = parent->head->x;
    new->y = parent->head->y + 1;
    break;
  case LEFT:
    new->x = parent->head->x - 1;
    new->y = parent->head->y;
    break;
  default:
    break;
  }
  printf("new y: %hd x: %hd \n", new->y, new->x);
  printf("end of make_head()\n");
  return new;
}

void init_player(Parent *player, GameState *state) {
  Node *new_head = make_node(5, 4);
  player->head = new_head;
  player->tail = new_head;
  player->length = 1;
}

short check_tile(Parent *parent, short **board, dir move_dir) {
  switch (move_dir) {
  case UP:
    if (parent->head->y - 1 < 0) {
      return 187;
    }
    return board[parent->head->y - 1][parent->head->x];
    break;
  case RIGHT:
    if (parent->head->x + 1 == 18) {
      return 187;
    }
    return board[parent->head->y][parent->head->x + 1];
    break;
  case DOWN:
    if (parent->head->y + 1 == 9) {
      return 187;
    }
    return board[parent->head->y + 1][parent->head->x];
    break;
  case LEFT:
    if (parent->head->x - 1 < 0) {
      return 187;
    }
    return board[parent->head->y][parent->head->x - 1];
    break;
  default:
    break;
  }
}

void gen_food(GameState *state, short **board) {
  short new_x;
  short new_y;
  do {
    new_x = (short)GetRandomValue(0, 17);
    new_y = (short)GetRandomValue(0, 8);
    state->food->x = new_x;
    state->food->y = new_y;
  } while (board[new_y][new_x] == 1);

  board[new_y][new_x] = 2;
}

// Called once per tick rate (default = 1 second)
void tick_update(Parent *parent, GameState *state, short **board) {
  printf("%d \n", state->move_dir);
  short tile_value = check_tile(parent, board, state->move_dir);

  state->prev_dir = state->move_dir;

  if (tile_value == 1 || tile_value == 187) {
    state->mode = KILL;
    printf("game ended\n");
    return;
  } else if (tile_value == 0) {
    printf("tile value: %hd\n", tile_value);
    Node *new_head = make_head(parent, state->move_dir);
    parent->head->prev = new_head;
    new_head->next = parent->head;
    parent->head = new_head;

    Node *new_tail = parent->tail->prev;
    board[parent->tail->y][parent->tail->x] = 0;
    MemFree(parent->tail);
    parent->tail = new_tail;
    parent->tail->next = NULL;
  } else if (tile_value == 2) {
    PlaySound(state->sounds[0]);
    state->score += 1;
    printf("tile value: %hd\n", tile_value);

    Node *new_head = make_head(parent, state->move_dir);
    parent->head->prev = new_head;
    new_head->next = parent->head;
    parent->head = new_head;
    parent->length += 1;

    board[parent->head->y][parent->head->x] = 0;
  }

  // state->prev_dir = state->move_dir;

  board[parent->head->y][parent->head->x] = 1;
  Node *current_node = parent->head->next;
  while (current_node != NULL) {
    board[current_node->y][current_node->x] = 1;
    printf("y: %hd x: %hd \n", current_node->y, current_node->x);
    current_node = current_node->next;
  }

  if (tile_value == 2) {
    gen_food(state, board);
  }

  printf("end of tick update()\n---------------\n");
  // Node *new_head = make_head(parent, state->move_dir);
}

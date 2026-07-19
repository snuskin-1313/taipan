#pragma once
#include "data.h"
#include "raylib.h"

void read_input(GameState *state);
void init_player(Parent *parent, GameState *state);
short check_tile(Parent *parent, short **board, dir move_dir);
void tick_update(Parent *parent, GameState *state, short **board);
Node *make_head(Parent *parent, dir dir);
void gen_food(GameState *state, short **board);

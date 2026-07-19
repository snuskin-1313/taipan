#pragma once

#include "data.h"
#include "raylib.h"

void draw_board(Texture2D *board);
void draw_ui(GameState *state);
void draw_snake(Texture2D *body, Parent *parent, GameState *state);
void draw_food(Texture2D *food, GameState *state);
void draw_part(Texture2D *body, short offset, short x, short y, float rot);

float get_head_rot(GameState *state);
float get_tail_rot(Parent *parent);

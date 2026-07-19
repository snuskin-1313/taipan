#pragma once

#include "data.h"
#include "raylib.h"

void draw_board(Texture2D *board);
void draw_ui(GameState *state);
void draw_snake(Texture2D *body, Parent *parent);
void draw_food(Texture2D *food, GameState *state);

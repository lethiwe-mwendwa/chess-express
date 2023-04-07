#pragma once
#include "SDL.h"

SDL_Rect* findClickedRect(int x, int y);

Piece* findClickedPiece(int x, int y);

bool findClickedCords(int x, int y, int& row, int&column);
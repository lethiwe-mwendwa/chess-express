#pragma once
#include "SDL.h"

// This function takes in the x and y coordinate in the window
// If those points are inside a rect, then it returns a rect
// this uses "findclickedcoords" for efficiency
SDL_Rect* findClickedRect(int x, int y);

// This function takes in the x and y coordinate in the window
// If there is a rect at that location and a piece that lies at that location, it returns the piece
// this uses "findclickedcoords" for efficiency
Piece* findClickedPiece(int x, int y);

// This function takes in the x and y coordinate in the window
// If there is a rect at that location it changes the value of "row" and "column"
// to be where the rect lies in the 2D array boardTiles[][].
// this is if I dont need the specific piece or the specific rect, and just the row/column value
bool findClickedCords(int x, int y, int& row, int&column);
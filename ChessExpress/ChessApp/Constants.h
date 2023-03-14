#pragma once
#include "SDL.h"
#include "Piece.h"


// Declaring the features
const int SCREEN_WIDTH = 264;
const int SCREEN_HEIGHT = 359;


//We'll use this for bitwise calculation. These are the values of the pieces.

const int PAWN = 1;
const int KING = 2;
const int QUEEN = 3;
const int BISHOP = 4;
const int ROOK = 5;
const int KNIGHT = 6;
const int BLACK = 8;
const int WHITE = 0;
const int TYPE_MASK = 7;

const int boardSize=8;

extern const char* pieceImagePaths[][2];
extern SDL_Rect boardTiles[boardSize][boardSize];

extern Piece chessBoard[boardSize][boardSize];
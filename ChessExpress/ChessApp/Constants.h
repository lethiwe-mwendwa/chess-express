#pragma once
#include "SDL.h"
#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Pawn.h"

// Declaring the features
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern  int gameTileSize;
extern bool isDragging;
extern SDL_Rect mouseRect;
extern Piece* clickedPiece;

//We'll use this for bitwise calculation. These are the values of the pieces.

const int PAWN = 1;
const int KING = 2;
const int QUEEN = 3;
const int BISHOP = 4;
const int ROOK = 5;
const int KNIGHT = 6;
const int BLACK = 8;
//const int WHITE = 0;
const int WHITE = 16;
const int COLOUR_MASK = 24;
const int TYPE_MASK = 7;

const int boardSize=8;

extern const char titleImagePath[];
extern const char pressEnterImagePath[];

extern const char* chessExpressASCII;
extern const char* lethiweMwendwaASCII;


extern SDL_Rect boardTiles[boardSize][boardSize];

extern Piece* piecesOnBoard[boardSize][boardSize];

extern Piece* whiteKing;

extern Piece* blackKing;

//Fen stuff

extern const char startingFen[];

extern char piecePlacement[];
extern char playerTurn;
extern char castlingAbility[];
extern char enPassantTarget[];
extern char halfmoveClock[];
extern char fullmoveClock[];


extern char currentFen[];

extern const char* pieceImagePaths[][2];

extern const char* numPaths[boardSize];
extern const char* letterPaths[boardSize];

extern SDL_Texture* letterTextures[boardSize];
extern SDL_Texture* numTextures[boardSize];

extern SDL_Texture* blackTurnTexture;
extern SDL_Texture* whiteTurnTexture;

extern const char blackTurnPath[];
extern const char whiteTurnPath[];


extern SDL_Rect statusTile;
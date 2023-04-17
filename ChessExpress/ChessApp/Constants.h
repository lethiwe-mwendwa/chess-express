#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
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
extern const char menuImagePath[];

extern const char* chessExpressASCII;
extern const char* lethiweMwendwaASCII;

extern SDL_Rect boardTiles[boardSize][boardSize];

extern Piece* piecesOnBoard[boardSize][boardSize];

extern bool check;

extern bool checkmate;

extern bool menu;

extern bool chessStarted;

extern King* whiteKing;

extern King* blackKing;

//Fen stuff

extern const char startingFen[];

extern char piecePlacement[];
extern char playerTurn;
extern char castlingAbility[];
extern char enPassantTarget[];
extern char halfmoveClock[];
extern char fullmoveClock[];

extern Mix_Chunk * dieA;
extern Mix_Chunk * moveA;
extern Mix_Chunk * introA;
extern Mix_Chunk * startA;
extern Mix_Chunk * checkA;
extern Mix_Chunk * endGameA;

extern char currentFen[];

extern const char* pieceImagePaths[][2];

extern const char* numPaths[boardSize];
extern const char* letterPaths[boardSize];

extern SDL_Texture* letterTextures[boardSize];
extern SDL_Texture* numTextures[boardSize];

extern SDL_Texture* blackTurnTexture;
extern SDL_Texture* whiteTurnTexture;

extern SDL_Texture* blackCheckTexture;
extern SDL_Texture* whiteCheckTexture;

extern SDL_Texture* blackCheckMateTexture;
extern SDL_Texture* whiteCheckMateTexture;

const int MAX_PIECES = 16;
extern int numOfWhitePieces;
extern int numOfBlackPieces;
extern Piece* whitePieces[MAX_PIECES];
extern Piece* blackPieces[MAX_PIECES];


//BLACK, WHITE.
extern const char blackTurnPath[];
extern const char whiteTurnPath[];

extern const char blackCheckPath[];
extern const char whiteCheckPath[];

extern const char blackCheckMatePath[];
extern const char whiteCheckMatePath[];

// I will deal with you later
extern SDL_Rect* moveSquares[];

extern SDL_Rect statusTile;
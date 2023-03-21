#include "Constants.h"

const char* pieceImagePaths[][2] = {
	{ "assets/P.bmp", "assets/bP.bmp" },
	{ "assets/K.bmp", "assets/bK.bmp" },
	{ "assets/Q.bmp", "assets/bQ.bmp" },
	{ "assets/B.bmp", "assets/bB.bmp" },
	{ "assets/R.bmp", "assets/bR.bmp" },
	{ "assets/N.bmp", "assets/bN.bmp" }
};


SDL_Rect boardTiles[boardSize][boardSize];

Piece* piecesOnBoard[boardSize][boardSize] = {
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};

const char titleImagePath[] = "assets/ChessXpress.bmp";

const char startingFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char currentFen[] = "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2";

char piecePlacement[64] = { 0 };
char playerTurn = '-';
char castlingAbility[5] = { 0 };
char enPassantTarget[3] = { 0 };
char halfmoveClock[3] = { 0 };
char fullmoveClock[7] = { 0 };



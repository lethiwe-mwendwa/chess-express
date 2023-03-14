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

Piece chessBoard[boardSize][boardSize] = {
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}
};



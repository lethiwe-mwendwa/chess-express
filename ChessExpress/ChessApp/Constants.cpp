#include "Constants.h"

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;

int gameTileSize;
bool isDragging = false;
SDL_Rect mouseRect = {};
//visit this later
Piece* clickedPiece = new Pawn(NULL, NULL, NULL, NULL);

const char* pieceImagePaths[][2] = {
	{ "assets/P.bmp", "assets/bP.bmp" },
	{ "assets/K.bmp", "assets/bK.bmp" },
	{ "assets/Q.bmp", "assets/bQ.bmp" },
	{ "assets/B.bmp", "assets/bB.bmp" },
	{ "assets/R.bmp", "assets/bR.bmp" },
	{ "assets/N.bmp", "assets/bN.bmp" }
};

//SDL_Texture* pieceRenderCache[][2];


SDL_Rect boardTiles[boardSize][boardSize];

Piece* piecesOnBoard[boardSize][boardSize];

const char titleImagePath[] = "assets/ChessXpress.bmp";
const char pressEnterImagePath[] = "assets/pressEnter.bmp";

const char startingFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char currentFen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

char piecePlacement[64] = { 0 };
char playerTurn = '-';
char castlingAbility[5] = { 0 };
char enPassantTarget[3] = { 0 };
char halfmoveClock[3] = { 0 };
char fullmoveClock[7] = { 0 };



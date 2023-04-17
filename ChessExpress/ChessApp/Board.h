#pragma once
#include "SDL.h"
#include "Constants.h"

class Board
{
public:
	Board();
	static void drawBoard(SDL_Renderer* renderer, float width, float height);
	static void changeTurn(SDL_Renderer* renderer);
	static void fenSetup(SDL_Renderer* renderer, char fen[]);

	static void refreshAllAttackZones();

	static void toFen();

	static bool noPiecesCanUncheck();

	static void pieceDisplay(SDL_Renderer* renderer, Piece* selectedPiece = NULL);

	static void initBoardTextures(SDL_Renderer* renderer);

	static void chessNumDisplay(SDL_Renderer* renderer,int row);
	static void chessLetterDisplay(SDL_Renderer* renderer, int column);

	//static void drawBoard2(SDL_Renderer* renderer, float width, float height, Piece* selectedPiece = NULL);
	static void fenSplitter(char fen[]);

	static Pawn * lastPawnMoved;
	static SDL_Rect * enPassantRect;
	static char getChessCord(int row, int column);
	static void translateChessCord(char chessCord[]);

private:
	
};

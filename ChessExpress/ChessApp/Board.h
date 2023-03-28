#pragma once
#include "SDL.h"
#include "Constants.h"

class Board
{
public:
	Board();
	static void drawBoard(SDL_Renderer* renderer, float width, float height);
	static void fenSetup(SDL_Renderer* renderer, char fen[]);
	static void pieceDisplay(SDL_Renderer* renderer, Piece* selectedPiece = NULL);
	static void fenSplitter(char fen[]);

private:
	
};



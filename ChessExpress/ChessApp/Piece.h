#pragma once
#include "SDL.h"

class Piece
{
public:
	Piece(SDL_Renderer* renderer, int type, int row, int column);
	static void drawPeice(SDL_Renderer* renderer, int row, int column, int pieceType);

private:
	int pieceType;
	const char* piecePath;
	bool pieceAlive;
	static const char* getPiecePath(int pieceType);
	SDL_Rect* pieceRect;
	
};


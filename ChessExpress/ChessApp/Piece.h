#pragma once
#include "SDL.h"

class Piece
{
public:
	Piece(int type);
	static void drawPeice(SDL_Renderer* renderer, int column, int row, int pieceType);

private:
	int pieceType;
	const char* piecePath;
	bool pieceAlive;
	static const char* getPiecePath(int pieceType);
	
};


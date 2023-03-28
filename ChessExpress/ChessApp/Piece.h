#pragma once
#include "SDL.h"

class Piece
{
public:
	Piece(SDL_Renderer* renderer, int type, int row, int column);

	int pieceType;

	void drawPeice(SDL_Renderer* renderer, int row, int column);
	void drawPeice2(SDL_Renderer* renderer, SDL_Rect imageRectLocation);
	bool pieceAlive;
	SDL_Rect* pieceRect;
	const char* piecePath;
	static const char* getPiecePath(int pieceType);
private:
	

	
};


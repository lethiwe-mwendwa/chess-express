#pragma once
#include "SDL.h"

class Piece
{
public:
	Piece(SDL_Renderer* renderer, int type, int row, int column);

	int pieceType;
	int pieceRow;
	int pieceColumn;
	bool pieceAlive;
	SDL_Rect* pieceRect;
	const char* piecePath;
	SDL_Surface* pieceSurface;
	SDL_Texture* pieceTexture;

	void killPeice();
	
	void drawPeice(SDL_Renderer* renderer, int row, int column);
	void drawPeice2(SDL_Renderer* renderer, SDL_Rect imageRectLocation);
	
	void placePiece(SDL_Renderer* renderer, int x, int y);

	static const char* getPiecePath(int pieceType);
private:
	

	
};


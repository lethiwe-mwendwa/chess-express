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
	
	//void drawPeice(SDL_Renderer* renderer, int row, int column);
	void drawPeice(SDL_Renderer* renderer, SDL_Rect imageRectLocation);
	
	void getPieceTrans(int newColumn, int newRow, int& transColumn, int& transRow);

	void placePiece(SDL_Renderer* renderer, int x, int y);

	static const char* getPiecePath(int pieceType);

	virtual bool isMoveValid(int newColumn, int newRow) = 0;
	virtual bool isKillValid(int newColumn, int newRow) = 0;

	virtual void getAttackTiles(Piece* piece) = 0;
	virtual bool inAttackZone(int newColumn, int newRow) = 0;

private:
	

	
};


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

	void killPiece();
	
	//void drawPeice(SDL_Renderer* renderer, int row, int column);
	void drawPiece(SDL_Renderer* renderer, SDL_Rect imageRectLocation);
	
	void getPieceTrans(int newColumn, int newRow, int& transColumn, int& transRow);

	void placePiece(int x, int y);

	static const char* getPiecePath(int pieceType);

	virtual bool isMoveValid(int newColumn, int newRow) = 0;
	virtual bool isKillValid(int newColumn, int newRow) = 0;

	bool moveUnchecks(int newColumn, int newRow, Piece* pieceInTheWay = NULL);

	virtual void getAttackTiles();
	bool inAttackZone(int column, int row);

	void clearAttackTiles();

	static const int maxAttackTiles = 64;
	SDL_Rect* attackZone[maxAttackTiles];
	int numAttackTiles = 0;

	char toFEN();
	
};


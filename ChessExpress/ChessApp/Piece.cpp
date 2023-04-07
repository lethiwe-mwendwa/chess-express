#pragma once
#include "SDL.h"
#include "Piece.h"
#include "Constants.h"
#include <iostream>
#include "Inputs.h"
using namespace std;



Piece::Piece(SDL_Renderer* renderer,int type, int row, int column) {
	this->pieceType = type;
	this->piecePath = getPiecePath(type);
	this->pieceAlive = true;
	this->pieceRow = row;
	this->pieceColumn = column;
	this->pieceRect = &boardTiles[row][column];
	this->pieceSurface = NULL;

	pieceSurface = SDL_LoadBMP(getPiecePath(this->pieceType));

	if (NULL == pieceSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}

	this->pieceTexture = SDL_CreateTextureFromSurface(renderer, pieceSurface);
	SDL_FreeSurface(pieceSurface);
	
	
	//drawPeice(renderer, row, column);
	
	
};

const char* Piece::getPiecePath(int pieceType) {

	int colourIndex = 0;
	int typeIndex = 0;
	//BIG NOTE. if I dont put type index as 0, it gets used and ignores the

	if (pieceType & BLACK) {
		colourIndex = 1;
	}
	switch (pieceType & TYPE_MASK) {
	case(PAWN):
		typeIndex = 0;
		break;
	case(KING):
		typeIndex = 1;
		break;
	case(QUEEN):
		typeIndex = 2;
		break;
	case(BISHOP):
		typeIndex = 3;
		break;
	case(ROOK):
		typeIndex = 4;
		break;
	case(KNIGHT):
		typeIndex = 5;
		break;
	}
	return(pieceImagePaths[typeIndex][colourIndex]);
};

void Piece::killPeice()
{
	this->pieceAlive = false;
	piecesOnBoard[this->pieceRow][this->pieceColumn] = NULL;
	delete this;
}

void Piece::drawPeice(SDL_Renderer* renderer, int row, int column) {
	//SDL_Surface* imageSurface = NULL;

	//imageSurface = SDL_LoadBMP(getPiecePath(this->pieceType));
	//imageSurface = SDL_LoadBMP(getPiecePath(this->pieceType));

	//if (NULL == imageSurface) {
	//	cout << "SDL error bozo" << SDL_GetError();
	//}
	//SDL_Rect imageRectLocation = boardTiles[row][column];

	//SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	//SDL_FreeSurface(imageSurface);

	//SDL_RenderCopy(renderer, this->pieceTexture, NULL, &imageRectLocation);
	//SDL_DestroyTexture(imageTexture);


};

void Piece::drawPeice2(SDL_Renderer* renderer, SDL_Rect imageRectLocation) {


	SDL_RenderCopy(renderer, this->pieceTexture, NULL, &imageRectLocation);
	//SDL_DestroyTexture(imageTexture);


};

void Piece::placePiece(SDL_Renderer* renderer, int x, int y) {

	clickedPiece = this;

	SDL_Rect newLocation = *(findClickedRect(x, y));

	int oldRow = clickedPiece->pieceRow;
	int oldColumn = clickedPiece->pieceColumn;

	int newRow;
	int newColumn;
	findClickedCords(x, y, newRow, newColumn);

	clickedPiece->pieceRow = newRow;
	clickedPiece->pieceColumn = newColumn;


	// black piece tried killing itself?
	//if (not((oldRow,oldColumn) == (newRow,newColumn))) {
	piecesOnBoard[newRow][newColumn] = clickedPiece;
	piecesOnBoard[oldRow][oldColumn] = NULL;


	clickedPiece->drawPeice2(renderer, newLocation);

};

// seperate into models, view, controller
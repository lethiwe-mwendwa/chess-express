#pragma once
#include "SDL.h"
#include "Piece.h"
#include "Constants.h"
#include <iostream>
using namespace std;



Piece::Piece(SDL_Renderer* renderer,int type, int row, int column) {
	this->pieceType = type;
	this->piecePath = getPiecePath(type);
	this->pieceAlive = true;
	this->pieceRow = row;
	this->pieceColumn = column;
	this->pieceRect = &boardTiles[row][column];
	
	
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

void Piece::drawPeice(SDL_Renderer* renderer, int row, int column) {
	SDL_Surface* imageSurface = NULL;

	//imageSurface = SDL_LoadBMP(getPiecePath(this->pieceType));
	imageSurface = SDL_LoadBMP(getPiecePath(this->pieceType));

	if (NULL == imageSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}
	SDL_Rect imageRectLocation = boardTiles[row][column];

	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);

	SDL_RenderCopy(renderer, imageTexture, NULL, &imageRectLocation);
	SDL_DestroyTexture(imageTexture);


};

void Piece::drawPeice2(SDL_Renderer* renderer, SDL_Rect imageRectLocation) {
	SDL_Surface* imageSurface = NULL;

	//imageSurface = SDL_LoadBMP(getPiecePath(this->pieceType));
	imageSurface = SDL_LoadBMP(getPiecePath(this->pieceType));

	if (NULL == imageSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}

	SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
	SDL_FreeSurface(imageSurface);

	SDL_RenderCopy(renderer, imageTexture, NULL, &imageRectLocation);
	SDL_DestroyTexture(imageTexture);


};

void Piece::drawPeiceE(SDL_Renderer* renderer, SDL_Rect imageRectLocation) {
	//pieceSurface = SDL_LoadBMP(getPiecePath(this->pieceType));
	SDL_Surface* pieceSurface = SDL_LoadBMP(getPiecePath(this->pieceType));
	if (NULL == pieceSurface) {
		cout << "SDL error bozo" << SDL_GetError();
	}

	SDL_Texture* pieceTexture = SDL_CreateTextureFromSurface(renderer, pieceSurface);
	SDL_FreeSurface(pieceSurface);
	SDL_RenderCopy(renderer, pieceTexture, NULL, &imageRectLocation);
	SDL_DestroyTexture(pieceTexture);




};

// seperate into models, view, controller
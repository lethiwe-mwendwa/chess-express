#pragma once
#include "SDL.h"
#include "Piece.h"
#include "Constants.h"
#include <iostream>
#include "Inputs.h"
#include "Board.h"
#include "Game.h"

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

void Piece::killPiece()
{
	this->pieceAlive = false;
	piecesOnBoard[this->pieceRow][this->pieceColumn] = NULL;
	SDL_DestroyTexture(this->pieceTexture);
	delete this;
}

void Piece::getAttackTiles()
{
	this->clearAttackTiles();

	for (int i = 0; i < maxAttackTiles; i++) {
		this->attackZone[i] = new SDL_Rect();
	}

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (this->isMoveValid(j, i) and (&boardTiles[i][j] != this->pieceRect)) {
				this->attackZone[this->numAttackTiles++] = &boardTiles[i][j];
			}
		}
	}

}

bool Piece::inAttackZone(int column, int row)
{
	for (int i = 0; i < maxAttackTiles; i++) {
		if (this->attackZone[i] == &boardTiles[row][column]) {
			return true;
		}
	}
	return false;
}

/*
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
*/

void Piece::drawPiece(SDL_Renderer* renderer, SDL_Rect imageRectLocation) {
	SDL_RenderCopy(renderer, this->pieceTexture, NULL, &imageRectLocation);

};

void Piece::getPieceTrans(int newColumn, int newRow, int &transColumn, int &transRow) {
	transColumn = this->pieceColumn - newColumn;
	transRow = this->pieceRow - newRow;
}

void Piece::placePiece(int x, int y) {

	clickedPiece = this;

	SDL_Rect* newLocation = findClickedRect(x, y);

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

	this->pieceRect = newLocation;
	

};

void Piece::clearAttackTiles() {
	for (int i = 0; i < numAttackTiles && i < maxAttackTiles; i++) {
		//delete attackZone[i];
		this->attackZone[i] = nullptr;
	}
	this->numAttackTiles = 0;
}

bool Piece::moveUnchecks(int newColumn, int newRow, Piece* pieceInTheWay){

	bool checkTemp = check;
	SDL_Renderer* nullRenderer = NULL;
	Piece* pieceTemp = pieceInTheWay;

	//simulate the move
	int oldRow = this->pieceRow;
	int oldColumn = this->pieceColumn;

	piecesOnBoard[newRow][newColumn] = this;
	piecesOnBoard[oldRow][oldColumn] = NULL;
	setCheckValue(nullRenderer);
	
	// undo move
	piecesOnBoard[oldRow][oldColumn] = this;
	if (pieceInTheWay) {
		piecesOnBoard[oldRow][oldColumn] = pieceTemp;
	}
	piecesOnBoard[newRow][newColumn] = NULL;
	Board::refreshAllAttackZones();
	
	//check if move unchecks king
	if (check) {
		check = checkTemp;
		return false;
	}
	else {
		check = checkTemp;
		return true;
	}
	

}

char Piece::toFEN() {
	if (this->pieceType & BLACK) {
		switch (this->pieceType & TYPE_MASK) {
		case(ROOK):
			return 'r';
			break;
		case(KNIGHT):
			return 'n';
			break;
		case(BISHOP):
			return 'b';
			break;
		case(QUEEN):
			return 'q';
			break;
		case(KING):
			return 'k';
			break;
		case(PAWN):
			return 'p';
			break;
		}
	}
	else {
		switch (this->pieceType & TYPE_MASK) {
		case(ROOK):
			return 'R';
			break;
		case(KNIGHT):
			return 'N';
			break;
		case(BISHOP):
			return 'B';
			break;
		case(QUEEN):
			return 'Q';
			break;
		case(KING):
			return 'K';
			break;
		case(PAWN):
			return 'P';
			break;
		}
	}
	return ' ';
	
}
#include "Pawn.h"
#include "Constants.h"
#include <iostream>
using namespace std;

bool Pawn::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);

	if (this->pieceType & WHITE) {
		if (
			(transRow == validMovesW[0][0] and transColumn == validMovesW[0][1]) or
			(transRow == validMovesW[1][0] and transColumn == validMovesW[1][1] and (not this->hasMovedYet) and Pawn::isPathClear(newRow))
			) {
			this->hasMovedYet = true;
			return true;
		}
	}
	else if (this->pieceType & BLACK) {
		if (
			(transRow == validMovesB[0][0] and transColumn == validMovesB[0][1]) or
			(transRow == validMovesB[1][0] and transColumn == validMovesB[1][1] and (not this->hasMovedYet) and Pawn::isPathClear(newRow))
			) {
			this->hasMovedYet = true;
			return true;
		}
	}


	return false;
}

bool Pawn::isKillValid(int newColumn, int newRow)
{
	//its looking at an empty place??	
	if ((piecesOnBoard[newRow][newColumn]->pieceType & COLOUR_MASK) != (this->pieceType & COLOUR_MASK)) {
	}
	else {
		return false;
	}

	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);

	if (this->pieceType & WHITE) {
		if (
			(transRow == validMovesW[2][0] and transColumn == validMovesW[2][1]) or
			(transRow == validMovesW[3][0] and transColumn == validMovesW[3][1])
			) {
			this->hasMovedYet = true;
			return true;
		}
	}
	else if (this->pieceType & BLACK) {
		if (
			(transRow == validMovesB[2][0] and transColumn == validMovesB[2][1]) or
			(transRow == validMovesB[3][0] and transColumn == validMovesB[3][1])
			) {
			this->hasMovedYet = true;
			return true;
		}
	}

	return false;
}

bool Pawn::isPathClear(int newRow)
{
	int rowIncrease = 1;
	if (newRow - this->pieceRow < 0) {
		rowIncrease = -1;
	}
	int rowToCheck = this->pieceRow+ rowIncrease;

	if (piecesOnBoard[rowToCheck][this->pieceColumn] != NULL) {
		return false;
	}
	else {
		return true;
	}
}

void Pawn::getAttackTiles(){
	clearAttackTiles();

	for (int i = 0; i < maxAttackTiles; i++) {
		attackZone[i] = new SDL_Rect();
	}

	if (this->pieceType & WHITE) {
		if (this->pieceRow > 0 and this->pieceColumn > 0) {
			attackZone[numAttackTiles++] = &boardTiles[this->pieceRow - 1][this->pieceColumn - 1];
		}
		if (this->pieceRow > 0 and this->pieceColumn < 7) {
			attackZone[numAttackTiles++] = &boardTiles[this->pieceRow - 1][this->pieceColumn + 1];
		}
		
	}
	else if (this->pieceType & BLACK) {
		if (this->pieceRow < 7 and this->pieceColumn > 0) {
			attackZone[numAttackTiles++] = &boardTiles[this->pieceRow + 1][this->pieceColumn - 1];
		}
		if (this->pieceRow < 7 and this->pieceColumn < 7) {
			attackZone[numAttackTiles++] = &boardTiles[this->pieceRow + 1][this->pieceColumn + 1];
		}
	}

}

const int Pawn::validMovesW[Pawn::validMoveLen][2] = {
		{1,0},{2,0},{1,-1},{1,1}
};

const int Pawn::validMovesB[Pawn::validMoveLen][2] = {
		{-1,0},{-2,0},{-1,-1},{-1,1}
};
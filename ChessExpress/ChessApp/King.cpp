#include "Constants.h"

bool King::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);
	int transPoints[] = { abs(transRow), abs(transColumn) };

	for (int i = 0; i < validMoveLen; i++) {
		for (int j = 0; j < 2; j++) {
			if ((transPoints[0] == validMoves[i][0] && transPoints[1] == validMoves[i][1])) {
				return true;
			}
		}
	}
	return false;
}

bool King::isKingMoveSafe(int newColumn, int newRow)
{
	if (King::isMoveValid(newColumn, newRow) and (not this->inDanger(newColumn, newRow))){
		return true;
	}
	return false;

	
}

bool King::isKillValid(int newColumn, int newRow)
{
	if (King::isKingMoveSafe(newColumn, newRow) and ((piecesOnBoard[newRow][newColumn]->pieceType & COLOUR_MASK) != (this->pieceType & COLOUR_MASK))) {
		return true;
	}
	return false;
}

bool King::inDanger(int column, int row) {
	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (piecesOnBoard[i][j] and 
				(this->pieceType & COLOUR_MASK) != (piecesOnBoard[i][j]->pieceType & COLOUR_MASK)) {

				if (piecesOnBoard[i][j]->inAttackZone(column, row)) {
					return true;
				}

			}
		}
	}
	return false;
}

bool King::trapped()
{
	// lift king
	piecesOnBoard[this->pieceRow][this->pieceColumn] = NULL;
	Board::refreshAllAttackZones();
	piecesOnBoard[this->pieceRow][this->pieceColumn] = this;

	for (int i = 0; i < boardSize; i++) {
		for (int j = 0; j < boardSize; j++) {
			if (piecesOnBoard[i][j]) {
				if (this->isKillValid(j, i) and not this->inDanger(j, i)) {
					Board::refreshAllAttackZones();
					return false;
				}
			}
			else {
				if (this->isMoveValid(j, i) and not this->inDanger(j, i)) {
					Board::refreshAllAttackZones();
					return false;
				}
			}
			
		}
	}

	if (Board::noPiecesCanUncheck()) {
		Board::refreshAllAttackZones();
		return true;
	}
	Board::refreshAllAttackZones();
	return false;
	
}

const int King::validMoves[King::validMoveLen][2]{
		{1,1},{1,0},{0,1}
};
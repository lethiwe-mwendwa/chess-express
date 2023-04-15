#include "Rook.h"
#include "Constants.h"
#include <iostream>
using namespace std;

bool Rook::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);
	int transPoints[] = { abs(transRow), abs(transColumn) };

	if (Rook::isTransVorH(transPoints[0], transPoints[1]) and Rook::isPathClear(this->pieceColumn, this->pieceRow, newColumn, newRow)) {
		return true;
	}

	return false;
}

bool Rook::isKillValid(int newColumn, int newRow)
{
	if (Rook::isMoveValid(newColumn, newRow) and (piecesOnBoard[newRow][newColumn]->pieceType & COLOUR_MASK) != (this->pieceType & COLOUR_MASK)) {
		return true;
	}
	return false;
}

bool Rook::isTransVorH(int row, int column) {
	if (row == 0 or column == 0) {
		return true;
	}
	return false;
}

bool Rook::isPathClear(int oldColumn, int oldRow, int newColumn, int newRow)
{
	bool horizontal = false;
	bool vertical = false;
	int increase = 1;

	if (newColumn - oldColumn < 0 or newRow - oldRow < 0) {
		increase = -1;
	}

	if (newColumn - oldColumn == 0) {
		vertical = true;
	}
	else if (newRow - oldRow == 0) {
		horizontal = true;
	}

	int currentRow = oldRow;
	int currentColumn = oldColumn;

	while (currentRow != newRow or currentColumn != newColumn) {
		if (not(piecesOnBoard[currentRow][currentColumn] == piecesOnBoard[oldRow][oldColumn]) and piecesOnBoard[currentRow][currentColumn] != NULL) {
			return false;
		}

		if (vertical) {
			currentRow = currentRow + increase;
		}
		else if (horizontal) {
			currentColumn = currentColumn + increase;
		}
	}
	return true;

}

void Rook::getAttackTiles(Piece* piece)
{
}

bool Rook::inAttackZone(int newColumn, int newRow)
{
	return false;
}

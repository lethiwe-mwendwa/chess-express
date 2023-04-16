#include "Bishop.h"
#include "Constants.h"

bool Bishop::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);
	int transPoints[] = { abs(transRow), abs(transColumn) };

	if (Bishop::isTransD(transPoints[0], transPoints[1]) and Bishop::isPathClear(this->pieceColumn, this->pieceRow, newColumn, newRow)) {
		return true;
	}

	return false;
}

bool Bishop::isTransD(int row, int column) {
	
	if (row != 0 and row == column) {
		return true;
	}
	return false;
}

bool Bishop::isPathClear(int oldColumn, int oldRow, int newColumn, int newRow)
{
	int rowIncrease = 1;
	int colIncrease = 1;
	
	if (newColumn - oldColumn < 0 ) {
		colIncrease = -1;
	}
	if (newRow - oldRow < 0){
		rowIncrease = -1;
	}

	int currentRow = oldRow;
	int currentColumn = oldColumn;

	while (currentRow != newRow or currentColumn != newColumn) {
		if (not(piecesOnBoard[currentRow][currentColumn] == piecesOnBoard[oldRow][oldColumn]) and piecesOnBoard[currentRow][currentColumn] != NULL) {
			return false;
		}
		currentRow = currentRow + rowIncrease;
		currentColumn = currentColumn + colIncrease;

	}
	return true;

}

bool Bishop::isKillValid(int newColumn, int newRow)
{
	if (Bishop::isMoveValid(newColumn, newRow) and (piecesOnBoard[newRow][newColumn]->pieceType & COLOUR_MASK) != (this->pieceType & COLOUR_MASK)) {
		return true;
	}
	return false;
}

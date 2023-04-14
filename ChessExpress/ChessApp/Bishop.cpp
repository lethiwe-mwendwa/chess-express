#include "Bishop.h"
#include "Constants.h"

bool Bishop::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);
	int transPoints[] = { abs(transRow), abs(transColumn) };

	if (Bishop::isTransD(transPoints[0], transPoints[1])) {
		return true;
	}
	
	return false;
}

bool Bishop::isTransD(int row, int column) {
	if (row == column) {
		return true;
	}
	return false;
}

bool Bishop::isKillValid(int newColumn, int newRow)
{
	return Bishop::isMoveValid(newColumn, newRow);
}

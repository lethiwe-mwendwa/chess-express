#include "King.h"
#include "Constants.h"

bool King::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);
	int transPoints[] = { abs(transRow), abs(transColumn) };

	for (int i = 0; i < validMoveLen; i++) {
		for (int j = 0; j < 2; j++) {
			if (transPoints[0] == validMoves[i][0] && transPoints[1] == validMoves[i][1]) {
				return true;
			}
		}
	}
	return false;
}

bool King::isKillValid(int newColumn, int newRow)
{
	return King::isMoveValid(newColumn, newRow);
}

const int King::validMoves[King::validMoveLen][2]{
		{1,1},{1,0},{0,1}
};
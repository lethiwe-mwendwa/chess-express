#include "Knight.h"
#include "Constants.h"

bool Knight::isMoveValid(int newColumn, int newRow)
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

const int Knight::validMoves[Knight::validMoveLen][2] = {
		{2,1}, {1,2}
};

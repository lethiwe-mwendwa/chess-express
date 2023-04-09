#include "King.h"
#include "Constants.h"

int validMoveLen = 3;

bool King::isMoveValid(int newColumn, int newRow)
{
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);

	for (int i = 0; i < validMoveLen; i++) {
		if ((abs(transColumn), abs(transRow)) == this->validMoves[i]) {
			return true;
		}
	}
	return false;
}

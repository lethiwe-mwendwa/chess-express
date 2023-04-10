#include "Rook.h"
#include "Constants.h"
#include <iostream>
using namespace std;

bool Rook::isMoveValid(int newColumn, int newRow)
{
	cout << endl << "ROOOOOK" << endl;
	int transColumn;
	int transRow;
	this->getPieceTrans(newColumn, newRow, transColumn, transRow);
	int transPoints[] = { abs(transRow), abs(transColumn) };

	cout << endl << transRow << endl << transColumn << endl;

	if (Rook::isTransVorH(transPoints[0], transPoints[1])) {
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

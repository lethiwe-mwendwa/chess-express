#pragma once
#include "Piece.h"
class Rook : public Piece
{
	public:
	Rook(SDL_Renderer* renderer, int type, int row, int column) :
	Piece(renderer, type, row, column) {

	}
	bool isMoveValid(int newColumn, int newRow) override;
	bool isKillValid(int newColumn, int newRow) override;
	static bool isTransVorH(int row, int column);
	static bool isPathClear(int oldColumn, int oldRow, int newColumn, int newRow);
};


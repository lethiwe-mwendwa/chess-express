#pragma once
#include "Piece.h"
class Queen : public Piece
{
	public:
    Queen(SDL_Renderer* renderer, int type, int row, int column) :
	Piece(renderer, type, row, column) {

	}

	bool isMoveValid(int newColumn, int newRow) override;
};


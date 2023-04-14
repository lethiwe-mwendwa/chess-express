#pragma once
#include "Piece.h"

class Bishop : public Piece
{
	public:
	Bishop(SDL_Renderer* renderer, int type, int row, int column) : Piece(renderer, type, row, column) {

	}
	bool isMoveValid(int newColumn, int newRow) override;
	bool isKillValid(int newColumn, int newRow) override;
	static bool isTransD(int row, int column);

	
};


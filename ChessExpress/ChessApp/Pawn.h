#pragma once
#include "Piece.h"
#include "SDL.h"

class Pawn : public Piece
{
	public:
    Pawn(SDL_Renderer* renderer, int type, int row, int column) :
	Piece(renderer, type, row, column) {
		this->hasMovedYet = true;
	}

	bool hasMovedYet;

	static const int validMoveLen = 4;
	static const int validMovesW[validMoveLen][2];
	static const int validMovesB[validMoveLen][2];

	bool isMoveValid(int newColumn, int newRow) override;
};


#pragma once
#include "Piece.h"
#include "SDL.h"

class Pawn : public Piece
{
	public:
    Pawn(SDL_Renderer* renderer, int type, int row, int column) :
	Piece(renderer, type, row, column) {
		this->hasMovedYet = false;
	}

	bool hasMovedYet;

	static const int validMoveLen = 4;
	static const int validMovesW[validMoveLen][2];
	static const int validMovesB[validMoveLen][2];

	bool isMoveValid(int newColumn, int newRow) override;
	bool isKillValid(int newColumn, int newRow) override;

	bool isPathClear(int newRow);

	SDL_Rect* attackZone[];

	void getAttackTiles(Piece* piece) override;
	bool inAttackZone(int newColumn, int newRow) override;
};


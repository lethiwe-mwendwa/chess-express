#pragma once
#include "Piece.h"
class Queen : public Piece
{
	public:
    Queen(SDL_Renderer* renderer, int type, int row, int column) :
	Piece(renderer, type, row, column) {

	}

	bool isMoveValid(int newColumn, int newRow) override;
	bool isKillValid(int newColumn, int newRow) override;

	SDL_Rect* attackZone[];

	void getAttackTiles(Piece* piece) override;
	bool inAttackZone(int newColumn, int newRow) override;
};


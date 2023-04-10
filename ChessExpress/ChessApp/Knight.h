#pragma once
#include "Piece.h"
class Knight : public Piece
{
    public:
    Knight(SDL_Renderer* renderer, int type, int row, int column) :
    Piece(renderer, type, row, column) {

    }
    static const int validMoveLen = 2;
    static const int validMoves[validMoveLen][2];

    bool isMoveValid(int newColumn, int newRow) override;
};


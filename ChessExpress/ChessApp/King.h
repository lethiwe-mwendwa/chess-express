#pragma once
#include "Piece.h"
class King :
    public Piece
{
    public:
    King(SDL_Renderer* renderer, int type, int row, int column) :
    Piece(renderer, type, row, column) {

    }

    static const int validMoveLen = 3;
    static const int validMoves[validMoveLen][2];

    bool isMoveValid(int newColumn, int newRow) override;
};


#pragma once
#include "Piece.h"
class King :
    public Piece
{
    static int validMoveLen;
    int validMoves[validMoveLen] = {
        (1,1),(1,0),(0,1)
    };

    bool isMoveValid(int newColumn, int newRow);
};


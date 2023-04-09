#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
    int validMoves[2] = {
        (2,1),(1,2)
    };
};


#include "Constants.h"

bool Queen::isMoveValid(int newColumn, int newRow)
{
    int transColumn;
    int transRow;
    this->getPieceTrans(newColumn, newRow, transColumn, transRow);
    //int transPoints[] = { abs(transRow), abs(transColumn) };

    if ((Bishop::isTransD(abs(transRow), abs(transColumn)) and Bishop::isPathClear(this->pieceColumn, this->pieceRow, newColumn, newRow)) or
       (Rook::isTransVorH(abs(transRow), abs(transColumn)) and Rook::isPathClear(this->pieceColumn, this->pieceRow, newColumn, newRow))){
        return true;
    }
    return false;
}

bool Queen::isKillValid(int newColumn, int newRow)
{
    if (Queen::isMoveValid(newColumn, newRow) and (piecesOnBoard[newRow][newColumn]->pieceType & COLOUR_MASK) != (this->pieceType & COLOUR_MASK)) {
        return true;
    }
    return false;
}

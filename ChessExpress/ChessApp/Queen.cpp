#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Constants.h"

bool Queen::isMoveValid(int newColumn, int newRow)
{
    int transColumn;
    int transRow;
    this->getPieceTrans(newColumn, newRow, transColumn, transRow);
    //int transPoints[] = { abs(transRow), abs(transColumn) };

    if (Bishop::isTransD(abs(transRow), abs(transColumn)) or Rook::isTransVorH(abs(transRow), abs(transColumn))) {
        return true;
    }
    return false;
}

bool Queen::isKillValid(int newColumn, int newRow)
{
    return Queen::isMoveValid(newColumn, newRow);
}

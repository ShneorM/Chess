#include "Bishop.h"
#include "ChessBoard.h"
#include <cmath>

bool Bishop::isValidMove(const std::string& move, const ChessBoard& board) const
{
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    int rowDiff = std::abs(destRow - srcRow);
    int colDiff = std::abs(destCol - srcCol);

    
    if (rowDiff != colDiff) {
        return false;
    }

    
    int rowStep = (destRow > srcRow) ? 1 : -1;
    int colStep = (destCol > srcCol) ? 1 : -1;

    int r = srcRow + rowStep;
    int c = srcCol + colStep;

    while (r != destRow && c != destCol)
    {
        if (board.getPiece(r, c) != nullptr)
            return false;

        r += rowStep;
        c += colStep;
    }

    return true;
}

Piece* Bishop::clone() const
{
    return new Bishop(*this);
}

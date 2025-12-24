#include "Queen.h"
#include "ChessBoard.h"
#include <cmath>

bool Queen::isValidMove(const std::string& move, const ChessBoard& board) const
{
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    int rowDiff = std::abs(destRow - srcRow);
    int colDiff = std::abs(destCol - srcCol);

    if (srcRow == destRow || srcCol == destCol)
    {
        int stepRow = (destRow > srcRow) ? 1 : (destRow < srcRow ? -1 : 0);
        int stepCol = (destCol > srcCol) ? 1 : (destCol < srcCol ? -1 : 0);

        int r = srcRow + stepRow;
        int c = srcCol + stepCol;

        while (r != destRow || c != destCol)
        {
            if (board.getPiece(r, c))
                return false;
            r += stepRow;
            c += stepCol;
        }
    }
    else if (rowDiff == colDiff)
    {
        int rowStep = (destRow > srcRow) ? 1 : -1;
        int colStep = (destCol > srcCol) ? 1 : -1;

        int r = srcRow + rowStep;
        int c = srcCol + colStep;

        while (r != destRow && c != destCol)
        {
            if (board.getPiece(r, c))
                return false;
            r += rowStep;
            c += colStep;
        }
    }
    else
    {
        return false;
    }


    return true;
}


Piece* Queen::clone() const
{
	return new Queen(*this);
}

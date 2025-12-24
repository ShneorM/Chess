#include "Knight.h"
#include "ChessBoard.h"
#include <cmath>

bool Knight::isValidMove(const std::string& move, const ChessBoard& board) const
{
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    int rowDiff = std::abs(destRow - srcRow);
    int colDiff = std::abs(destCol - srcCol);

 
    bool isLShape = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    if (!isLShape)
        return false;

    return true;
}

Piece* Knight::clone() const
{
    return new Knight(*this);
}


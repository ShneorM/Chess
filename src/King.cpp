#include "King.h"
#include "ChessBoard.h"

bool King::isValidMove(const std::string& move, const ChessBoard& board) const
{
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    if (srcRow == destRow && srcCol == destCol)
        return false;


    int rowDiff = abs(destRow - srcRow);
    int colDiff = abs(destCol - srcCol);

    
    if (rowDiff <= 1 && colDiff <= 1)
    {
        const Piece* destPiece = board.getPiece(destRow, destCol);
        if (destPiece == nullptr || destPiece->isWhite() != this->isWhite())
        {
            return true;
        }
    }

    return false;
}



Piece* King::clone() const
{
    return new King(*this);
}
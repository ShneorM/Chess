#include "Pawn.h"
#include "ChessBoard.h"

bool Pawn::isValidMove(const std::string& move, const ChessBoard& board) const
{
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';

    int direction = isWhite() ? 1 : -1;
    int startRow = isWhite() ? 1 : 6;

    const Piece* destPiece = board.getPiece(destRow, destCol);

    int rowDiff = destRow - srcRow;
    int colDiff = destCol - srcCol;

    // צעד רגיל קדימה
    if (colDiff == 0 && rowDiff == direction)
    {
        if (!destPiece)
            return true;
    }

    // צעד כפול משורה התחלתית
    if (colDiff == 0 && rowDiff == 2 * direction && srcRow == startRow)
    {
        int betweenRow = srcRow + direction;
        if (!destPiece && !board.getPiece(betweenRow, srcCol))
            return true;
    }

    // אכילה באלכסון
    if (std::abs(colDiff) == 1 && rowDiff == direction)
    {
        if (destPiece && destPiece->isWhite() != this->isWhite())
            return true;
    }

    // כל מצב אחר לא חוקי
    return false;
}


Piece* Pawn::clone() const
{
    return new Pawn(*this);
}

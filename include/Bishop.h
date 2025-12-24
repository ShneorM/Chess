#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
    Bishop(char symbol) : Piece(symbol, "Bishop") {}

    bool isValidMove(const std::string& move, const ChessBoard& board) const override;

    Piece* clone() const override;
};

#pragma once
#include "Piece.h"

class King : public Piece
{
public:
    King(char symbol) : Piece(symbol, "King") {}

    bool isValidMove(const std::string& move, const ChessBoard& board) const override;
    Piece* clone() const override;
};

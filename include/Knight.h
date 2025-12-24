#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
    Knight(char symbol) : Piece(symbol, "Knight") {}

    bool isValidMove(const std::string& move, const ChessBoard& board) const override;

    Piece* clone() const override;
};

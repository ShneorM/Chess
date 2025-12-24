#pragma once
#include "Piece.h"

class Pawn : public Piece
{
public:
    Pawn(char symbol) : Piece(symbol, "Pawn") {}

    bool isValidMove(const std::string& move, const ChessBoard& board) const override;

    Piece* clone() const override;
};

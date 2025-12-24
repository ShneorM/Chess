#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
    Queen(char symbol) : Piece(symbol, "Queen") {}

    bool isValidMove(const std::string& move, const ChessBoard& board) const override;

    Piece* clone() const override;
};

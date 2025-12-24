#pragma once
#include "Piece.h"


class Rook : public Piece
{
public:
	Rook(char symbol) : Piece(symbol, "Rook") {}

	bool isValidMove(const string& move, const ChessBoard& board) const override;
	Piece* clone() const override;

};


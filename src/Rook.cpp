#pragma once
#include "Rook.h"
#include "ChessBoard.h"


bool Rook::isValidMove(const string& move, const ChessBoard& board) const
{
	int srcRow = move[0] - 'a';
	int srcCol = move[1] - '1';
	int destRow = move[2] - 'a';
	int destCol = move[3] - '1';

	
	if (srcRow != destRow && srcCol != destCol || srcRow == destRow && srcCol == destCol)
	{
		return false; 
	}

	if (srcRow == destRow)
	{ 
		int start = (srcCol < destCol) ? srcCol + 1 : destCol + 1;
		int end = (srcCol > destCol) ? srcCol : destCol;
		for (int col = start; col < end; ++col)
		{
			if (board.getPiece(srcRow, col))
			{
				return false;
			}
		}
	}
	else
	{ 
		int start = (srcRow < destRow) ? srcRow + 1 : destRow + 1;
		int end = (srcRow > destRow) ? srcRow : destRow;
		for (int row = start; row < end; ++row)
		{
			if (board.getPiece(row, srcCol))
			{
				return false; 
			}
		}
	}

	return true; 

}

Piece* Rook::clone() const 
{
	return new Rook(*this);
}
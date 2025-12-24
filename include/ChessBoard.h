#pragma once

#include "Piece.h"
#include "Rook.h"
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "Pawn.h"

const int _BOARD_SIZE = 8;

class ChessBoard
{
private:
	bool turn = true;
	Piece* board[_BOARD_SIZE][_BOARD_SIZE ] = { nullptr };


	bool whiteKingMoved = false; //A5
	bool whiteRookLeftMoved = false;  // A1
	bool whiteRookRightMoved = false; // A8


	bool blackKingMoved = false; // H5
	bool blackRookLeftMoved = false;  // H1
	bool blackRookRightMoved = false; // H8


public:
	Piece* getPiece(int row, int col) const;
	int makeMove(const string& move);
	void updateBoard(const string& move);
	bool isKingInCheck(int kingRow, int kingCol, bool isWhite);
	string findKingPosition(bool isWhite) const;


	ChessBoard(const string& boardStr);
	ChessBoard(const ChessBoard& other);
	~ChessBoard();

	bool isCastlingMove(const string& move, bool isWhite);
	int performCastling(const string& move, bool isWhite);



	ChessBoard& operator=(const ChessBoard& other);


};

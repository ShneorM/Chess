#pragma once
#include "ChessBoard.h"
#include "ChessExceptions.h"



Piece* ChessBoard::getPiece(int row, int col) const
{
	return board[row][col];
}


int ChessBoard::makeMove(const string& move)
{
	int srcRow = move[0] - 'a';
	int srcCol = move[1] - '1';
	int destRow = move[2] - 'a';
	int destCol = move[3] - '1';

	// check source piece
	Piece* piece = getPiece(srcRow, srcCol);
	if (!piece)
		throw InvalidMoveException("No piece at source square.");

	if (piece->isWhite() != turn)
		throw InvalidMoveException("The piece belongs to the opponent.");

	// check destination
	Piece* destPiece = getPiece(destRow, destCol);
	if (destPiece && destPiece->isWhite() == turn)
		throw InvalidMoveException("Destination occupied by your own piece.");

	// castling (still returns 42 as success)
	if (isCastlingMove(move, turn))
		return performCastling(move, turn);

	// regular move
	bool moveResult = piece->isValidMove(move, *this);
	if (!moveResult)
		throw InvalidMoveException("Illegal move for this piece.");

	auto tempBoard = *this;
	updateBoard(move);

	// update movement flags
	char symbol = piece->getSymbol();
	if (symbol == 'K') whiteKingMoved = true;
	if (symbol == 'k') blackKingMoved = true;

	if (symbol == 'R') 
	{
		if (srcRow == 0 && srcCol == 0) whiteRookLeftMoved = true;
		if (srcRow == 0 && srcCol == 7) whiteRookRightMoved = true;
	}
	if (symbol == 'r') 
	{
		if (srcRow == 7 && srcCol == 0) blackRookLeftMoved = true;
		if (srcRow == 7 && srcCol == 7) blackRookRightMoved = true;
	}

	// check for self-check
	string kingPosition = findKingPosition(turn);
	if (isKingInCheck(kingPosition[0] - 'a', kingPosition[1] - '1', turn)) 
	{
		*this = tempBoard;
		throw CheckException("Move would result in check.");
	}

	// check if move causes check to opponent
	string enemyKingPosition = findKingPosition(!turn);
	if (isKingInCheck(enemyKingPosition[0] - 'a', enemyKingPosition[1] - '1', !turn)) 
	{
		turn = !turn;
		return 41; // move legal + causes check
	}

	turn = !turn;
	return 42; // move legal
}




bool ChessBoard::isKingInCheck(int kingRow, int kingCol, bool isWhite)
{
	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (board[row][col] && board[row][col]->getSymbol() != (isWhite ? 'K' : 'k'))
			{
				string move = { char(row + 'a'), char(col + '1'), char(kingRow + 'a'), char(kingCol + '1') };

				if (board[row][col]->isWhite() != isWhite && board[row][col]->isValidMove(move, *this))
				{
					return true;
				}
			}
		}
	}
	return false;
}



void ChessBoard::updateBoard(const string& move)
{
	int srcRow = move[0] - 'a';
	int srcCol = move[1] - '1';
	int destRow = move[2] - 'a';
	int destCol = move[3] - '1';

	if (board[destRow][destCol])
	{
		delete board[destRow][destCol];
		board[destRow][destCol] = nullptr;
	}
	board[destRow][destCol] = board[srcRow][srcCol];
	board[srcRow][srcCol] = nullptr;
}

string ChessBoard::findKingPosition(bool isWhite) const
{
	char kingSymbol = isWhite ? 'K' : 'k';

	for (int row = 0; row < 8; ++row)
	{
		for (int col = 0; col < 8; ++col)
		{
			if (board[row][col] && board[row][col]->getSymbol() == kingSymbol)
			{
				char rowChar = char('a' + row);
				char colChar = char('1' + col);
				return { rowChar, colChar };
			}
		}
	}
	return "--";
}



ChessBoard::ChessBoard(const string& boardStr)
{
	for (int i = 0; i < boardStr.size(); ++i)
	{
		int row = i / _BOARD_SIZE;
		int col = i % _BOARD_SIZE;
		char s = boardStr[i];

		if (s != '#')
		{
			switch (s)
			{
			case 'R': case 'r':
				board[row][col] = new Rook(s);
				break;
			case 'N': case 'n':
				board[row][col] = new Knight(s);
				break;
			case 'B': case 'b':
					board[row][col] = new Bishop(s);
					break;
			case 'K': case 'k':
				board[row][col] = new King(s);
				break;
			case 'Q': case 'q':
				board[row][col] = new Queen(s);
				break;
			case 'P': case 'p':
				board[row][col] = new Pawn(s);
				break;
			}
		}
	}
}

ChessBoard::ChessBoard(const ChessBoard& other)
{
	for (int i = 0; i < _BOARD_SIZE; ++i)
	{
		for (int j = 0; j < _BOARD_SIZE; ++j)
		{
			if (other.board[i][j])
				board[i][j] = other.board[i][j]->clone();
			else
				board[i][j] = nullptr;
		}
	}
	this->turn = other.turn;
}

ChessBoard::~ChessBoard()
{
	for (int row = 0; row < _BOARD_SIZE; ++row)
	{
		for (int col = 0; col < _BOARD_SIZE; ++col)
		{
			if (board[row][col])
			{
				delete board[row][col];
				board[row][col] = nullptr;
			}
		}
	}
}

bool ChessBoard::isCastlingMove(const string& move, bool isWhite) 
{
	// copy board to simulate move without modifying original
	ChessBoard tempBoard = *this;

	// king position before castling
	int row = isWhite ? 0 : 7;
	int col = 4;

	// check if king is currently in check
	if (isKingInCheck(row, col, isWhite))
		return false;

	if (isWhite) 
	{
		if (move == "a5a7") 
		{ // short
			if (whiteKingMoved || whiteRookRightMoved) return false;
			if (board[0][5] || board[0][6]) return false;

			// simulate king moving through a6 and a7
			if (tempBoard.isKingInCheck(0, 5, true)) return false;
			if (tempBoard.isKingInCheck(0, 6, true)) return false;

			return true;
		}
		if (move == "a5a3") 
		{ // long
			if (whiteKingMoved || whiteRookLeftMoved) return false;
			if (board[0][1] || board[0][2] || board[0][3]) return false;

			if (tempBoard.isKingInCheck(0, 3, true)) return false;
			if (tempBoard.isKingInCheck(0, 2, true)) return false;

			return true;
		}
	}
	else 
	{
		if (move == "h5h7") 
		{ // short
			if (blackKingMoved || blackRookRightMoved) return false;
			if (board[7][5] || board[7][6]) return false;

			if (tempBoard.isKingInCheck(7, 5, false)) return false;
			if (tempBoard.isKingInCheck(7, 6, false)) return false;

			return true;
		}
		if (move == "h5h3")
		{ // long
			if (blackKingMoved || blackRookLeftMoved) return false;
			if (board[7][1] || board[7][2] || board[7][3]) return false;

			if (tempBoard.isKingInCheck(7, 3, false)) return false;
			if (tempBoard.isKingInCheck(7, 2, false)) return false;

			return true;
		}
	}

	return false;
}

int ChessBoard::performCastling(const string& move, bool isWhite) {
	if (isWhite) {
		if (move == "a5a7") { // short
			// move king
			board[0][6] = board[0][4];
			board[0][4] = nullptr;

			// delete destination if needed
			if (board[0][5]) delete board[0][5];

			// move rook from a8 (0,7) to a6 (0,5)
			board[0][5] = board[0][7];
			board[0][7] = nullptr;

			whiteKingMoved = whiteRookRightMoved = true;
		}
		else if (move == "a5a3") { // long
			// move king
			board[0][2] = board[0][4];
			board[0][4] = nullptr;

			if (board[0][3]) delete board[0][3];

			// move rook from a1 (0,0) to a4 (0,3)
			board[0][3] = board[0][0];
			board[0][0] = nullptr;

			whiteKingMoved = whiteRookLeftMoved = true;
		}
	}
	else {
		if (move == "h5h7") { // short
			board[7][6] = board[7][4];
			board[7][4] = nullptr;

			if (board[7][5]) delete board[7][5];

			// move rook from h8 (7,7) to h6 (7,5)
			board[7][5] = board[7][7];
			board[7][7] = nullptr;

			blackKingMoved = blackRookRightMoved = true;
		}
		else if (move == "h5h3") { // long
			board[7][2] = board[7][4];
			board[7][4] = nullptr;

			if (board[7][3]) delete board[7][3];

			// move rook from h1 (7,0) to h4 (7,3)
			board[7][3] = board[7][0];
			board[7][0] = nullptr;

			blackKingMoved = blackRookLeftMoved = true;
		}
	}

	turn = !turn;
	return 42;
}



ChessBoard& ChessBoard::operator=(const ChessBoard& other)
{
	if (this == &other)
		return *this; 
	
	for (int i = 0; i < _BOARD_SIZE; ++i)
	{
		for (int j = 0; j < _BOARD_SIZE; ++j)
		{
			delete board[i][j];
			board[i][j] = nullptr;
		}
	}

	for (int i = 0; i < _BOARD_SIZE; ++i)
	{
		for (int j = 0; j < _BOARD_SIZE; ++j)
		{
			if (other.board[i][j])
				board[i][j] = other.board[i][j]->clone();
			else
				board[i][j] = nullptr;
		}
	}

	// Copy game state
	this->turn = other.turn;

	// Copy castling-related flags
	this->whiteKingMoved = other.whiteKingMoved;
	this->whiteRookLeftMoved = other.whiteRookLeftMoved;
	this->whiteRookRightMoved = other.whiteRookRightMoved;

	this->blackKingMoved = other.blackKingMoved;
	this->blackRookLeftMoved = other.blackRookLeftMoved;
	this->blackRookRightMoved = other.blackRookRightMoved;

	return *this;
}



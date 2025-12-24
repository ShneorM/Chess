// Chess
#include "Chess.h"
#include "ChessBoard.h"
#include "ChessExceptions.h"

int main()
{
	// string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	string board = "R###K##R###########################################ppppprnbqk##r";

	// myCode
	ChessBoard *chessBoard = new ChessBoard(board);
	// end of myCode

	Chess a(board);
	int codeResponse = 0;
	string res = a.getInput();
	while (res != "exit")
	{
		/*
		codeResponse value :
		Illegal movements :
		11 - there is not piece at the source
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination
		21 - illegal movement of that piece
		31 - this movement will cause you checkmate

		legal movements :
		41 - the last movement was legal and cause check
		42 - the last movement was legal, next turn
		*/

		/**/

		try
		{
			int result = chessBoard->makeMove(res);
			a.setCodeResponse(result);
		}
		catch (const InvalidMoveException &e)
		{
			a.setMessage(e.what());
		}
		catch (const CheckException &e)
		{
			a.setMessage(e.what());
		}
		catch (const exception &e)
		{
			a.setMessage(string("Unexpected error: ") + e.what());
		}

		cout << "code response >> " << codeResponse;

		a.setCodeResponse(codeResponse);
		res = a.getInput();
	}

	cout << endl
		 << "Exiting " << endl;

	delete chessBoard;

	return 0;
}
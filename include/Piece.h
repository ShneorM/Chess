#pragma once
#include <string>

using std::string; 
class ChessBoard;

class Piece 
{
protected:
    char symbol;
    string name;

public:
    Piece(char symbol, string name) : symbol(symbol), name(name) {}
    virtual ~Piece() {}
    char getSymbol() const { return symbol; }
    string getName() const { return name; }
    bool isWhite() const { return symbol >= 'A' && symbol <= 'Z'; }
    
    virtual Piece* clone() const = 0;
    virtual bool isValidMove(const string& move, const ChessBoard& board) const = 0;

};

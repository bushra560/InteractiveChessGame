//File name is piece.h to follow naming convension
#pragma once
#include<iostream>
#include<string>
#include<cmath>   
#include<cctype>
using namespace std;

extern bool whiteKingMoved;
extern bool blackKingMoved;
extern bool whiteRookAMoved;
extern bool whiteRookHMoved;
extern bool blackRookAMoved;
extern bool blackRookHMoved;
extern int lastDoublePawnRow;
extern int lastDoublePawnCol;
extern bool lastMoveWasDoublePawn;
extern string lastDoublePawnColor;


class Piece
{
	string color;//stores white or black
	int row;//current row position
	int col;//current column position
	char symbol;// p(pawn),R(Rook),K( Knight), B(Bishop), Q(Queen),Ki( King))

public:
	Piece(string c, int r, int co, char sym);
	/*:color(c),row(r),col(co),symbol(sym)*/

	virtual ~Piece();//virtual destructor to ensure proper cleanup of derived class objects through base class pointers
	string getColor();
	char getSymbol();
	int getRow();
	int getCol();
	//because we cannot access them directly
	void setPosition(int r, int co);//informing about the positions updating 

	virtual bool isValid_Move(int r, int co, Piece* board[8][8]) = 0;
	//Pure virtual function bcz there is no default behaviour of this function in the base class
	//Every piece must define its own movement
};
class Pawn :public Piece
{
public:
	Pawn(string c, int r, int co, char sym);
	~Pawn(); // Destructor for Pawn class
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement rule
	// a pawn can only move forward one square (or two squares on its first move)
};
class Rook : public Piece
{
public:
	Rook(string c, int r, int co, char sym);
	~Rook(); // Destructor for Rook class
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement
	//a rook can move in + shape but cannot jump over other pieces
};
class Knight :public Piece {
public:
	Knight(string c, int r, int co, char sym);
	~Knight(); // Destructor for Knight class
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement
	//Knight moves in an L shape and can jump over other pieces
};

class Bishop :public Piece {
public:
	Bishop(string c, int r, int co, char sym);
	~Bishop(); // Destructor for Bishop class
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement
	//Bishop moves diagonally and cannot jump over other pieces

};
class Queen : public Piece {
public:
	Queen(string c, int r, int co, char sym);
	~Queen(); // Destructor for Queen class
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Queen piece  must define its own movement
	//Queen can move in any direction (horizontally, vertically, diagonally) but cannot jump over other pieces
	//Queen movement combines both the rook and bishop.

};
class King : public Piece {
public:
	King(string c, int r, int co, char sym);
	~King(); // Destructor for King class
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//King can move one square in any direction (horizontally, vertically, diagonally) but cannot jump over other pieces
	//The king is the most important piece in chess. The objective of the game is to checkmate the opponent's king.
};
//***********************************
//===========Helper Functions=====
//***********************************

//Additional function to parse user input like "E2" to row and column indices
void parseInput(string pos, int& row, int& col);

// Function to check if a square is attacked by any piece of the opposite color
bool isSquareAttacked(int r, int co, const string& kingColor, Piece* board[8][8]);


//***********************************
//===========Special Moves Functions=====
//***********************************

// Move a piece normally
void makeMove(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol);

// En passant
bool canEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol,
	const string& turn,
	int lastDoublePawnRow, int lastDoublePawnCol,
	const string& lastDoublePawnColor, bool lastMoveWasDoublePawn);

void doEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol,
	const string& turn);

// Castling
bool canCastleKingSide(Piece* board[8][8], const string& color, int row, int col,
	bool kingMoved, bool rookMoved);

bool canCastleQueenSide(Piece* board[8][8], const string& color, int row, int col,
	bool kingMoved, bool rookMoved);

void doCastleKingSide(Piece* board[8][8], int row);
void doCastleQueenSide(Piece* board[8][8], int row);

// Promotion
bool canPromote(Piece* board[8][8], int row, int col);

void promotePawn(Piece* board[8][8], int row, int col, char choice, const string& color);


//***********************************
//===========Checkmate & InCheck =====
//***********************************
bool isMoveSafe(int fromR, int fromC, int toR, int toC, string color, Piece* board[8][8]);
	bool isInCheck(string color, Piece* board[8][8]);
	bool hasLegalMoves(string color, Piece* board[8][8]);

//***********************************
//=========== Draw Function =====
//***********************************
	bool hasInsufficientMaterial(Piece* board[8][8]);
	bool isStalemate(string color, Piece* board[8][8]);
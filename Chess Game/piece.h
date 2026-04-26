//File name is piece.h to follow naming convension
#pragma once
#include<iostream>
#include<string>
#include<cmath>   
using namespace std;

class Piece
{
	string color;//stores white or black
	int row;//current row position
	int col;//current column position
	char symbol;// p(pawn),R(Rook),K( Knight), B(Bishop), Q(Queen),Ki( King))

public:
	Piece(string c, int r, int co, char sym);
	/*:color(c),row(r),col(co),symbol(sym)*/

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

	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement rule
	// a pawn can only move forward one square (or two squares on its first move)
};
class Rook : public Piece
{
public:
	Rook(string c, int r, int co, char sym);

	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement
	//a rook can move in + shape but cannot jump over other pieces
};
class Knight :public Piece {
public:
	Knight(string c, int r, int co, char sym);

	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement
	//Knight moves in an L shape and can jump over other pieces
};

class Bishop :public Piece {
public:
	Bishop(string c, int r, int co, char sym);

	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Every piece must define its own movement
	//Bishop moves diagonally and cannot jump over other pieces

};
class Queen : public Piece {
public:
	Queen(string c, int r, int co, char sym);

	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//Queen piece  must define its own movement
	//Queen can move in any direction (horizontally, vertically, diagonally) but cannot jump over other pieces
	//Queen movement combines both the rook and bishop.

};
class King : public Piece {
public:
	King(string c, int r, int co, char sym);
	bool isValid_Move(int r, int co, Piece* board[8][8]) override;	//King can move one square in any direction (horizontally, vertically, diagonally) but cannot jump over other pieces
	//The king is the most important piece in chess. The objective of the game is to checkmate the opponent's king.
};

//Additional function to parse user input like "E2" to row and column indices
void parseInput(string pos, int& row, int& col);
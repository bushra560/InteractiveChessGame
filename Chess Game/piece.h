 //File name is piece.h to follow naming convension
#pragma once
#include<iostream>
#include<string>
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
	void setPosition(int r, int co);//informing about the positions uupdating 

	virtual bool isValid_Move(int r, int co) = 0;//Pure virtual function bcz there is no default behaviour of this function in the base class
	//Every piece must define its own movement
};
class Pawn :public Piece
{
public:
	Pawn(string c, int r, int co, char sym);

	bool isValid_Move(int r, int co) override;
	//Every piece must define its own movement rule

};
class Rook : public Piece
{
public:
	Rook(string c, int r, int co, char sym);

	bool isValid_Move(int r, int co) override;
	//Every piece must define its own movement
};
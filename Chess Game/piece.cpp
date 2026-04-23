#include"piece.h"// Including header file

Piece::Piece(string c, int r, int co, char sym)
	:color(c), row(r), col(co), symbol(sym)
{

}
string Piece::getColor()
{
	return color;
}
char Piece::getSymbol()
{
	return symbol;
}
int Piece::getRow()
{
	return row;
}

int Piece::getCol()
{
	return col;
}
void Piece::setPosition(int r, int co)
{
	//here updating he positions 
	row = r;
	col = co;
}
//***********************************
//===========PAWN implementation=====
//***********************************
Pawn::Pawn(string c, int r, int co, char sym)
	: Piece(c, r, co, 'P')
{
}
bool Pawn::isValid_Move(int r, int co)
{
	// White moves upward
	if (getColor() == "white")
	{
		return (r == getRow() - 1 && co == getCol());

	}
	// Black moves downward
	else
	{
		return (r == getRow() + 1 && co == getCol());
	}
}

//***********************************
//===========ROCK implementation=====
//***********************************
Rook::Rook(string c, int r, int co, char sym)
	: Piece(c, r, co, 'R')
{
}

bool Rook::isValid_Move(int r, int co)
{
	return (r == getRow() || co == getCol());
}

//***********************************
//===========Knight implementation=====
//***********************************



//***********************************
//===========BISHOP implementation=====
//***********************************

//***********************************
//===========QUEEN implementation=====
//***********************************

//***********************************
//===========KING implementation=====
//***********************************
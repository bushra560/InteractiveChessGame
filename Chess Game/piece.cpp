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
Knight::Knight(string c, int r, int co, char sym)
	: Piece(c, r, co, 'K')
{
}

bool Knight::isValid_Move(int r, int co)
{

	int rowDiff = abs(r - getRow());
	int colDiff = abs(co - getCol());
	return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);

}


//***********************************
//===========BISHOP implementation=====
//***********************************
Bishop::Bishop(string c, int r, int co, char sym)
	: Piece(c, r, co, 'B')
{
}
bool Bishop::isValid_Move(int r, int co)
{
	return abs(r - getRow()) == abs(co - getCol());
}
//***********************************
//===========QUEEN implementation=====
//***********************************
Queen::Queen(string c, int r, int co, char sym)
	: Piece(c, r, co, 'Q')
{
}
bool Queen::isValid_Move(int r, int co)
{
	return (r == getRow() || co == getCol()) || (abs(r - getRow()) == abs(co - getCol()));
}
//***********************************
//===========KING implementation=====A
//***********************************

King::King(string c, int r, int co, char sym)
	: Piece(c, r, co, 'K')
{
}
bool King::isValid_Move(int r, int co)
{
	int rowDiff = abs(r - getRow());
	int colDiff = abs(co - getCol());
	return (rowDiff <= 1 && colDiff <= 1);
}
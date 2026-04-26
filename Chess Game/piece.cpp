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
bool Pawn::isValid_Move(int r, int co, Piece* board[8][8])
{
	int currRow = getRow();
	int currCol = getCol();

	// WHITE PAWN
	if (getColor() == "white")
	{// First move can be two squares forward
		if (currRow == 6 && co == currCol && r == currRow - 2 &&
			board[currRow - 1][currCol] == nullptr &&
			board[r][co] == nullptr)
			return true;
		// Normal forward move
		if (co == currCol && r == currRow - 1 && board[r][co] == nullptr)
			return true;
		
		// Diagonal capture
		if (r == currRow - 1 && abs(co - currCol) == 1 &&
			board[r][co] != nullptr &&
			board[r][co]->getColor() != "white")
			return true;
	}
	else // BLACK PAWN
	{ // First move can be two squares forward
		if (currRow == 1 && co == currCol && r == currRow + 2 &&
			board[currRow + 1][currCol] == nullptr &&
			board[r][co] == nullptr)
			return true;
		// Normal forward move
		if (co == currCol && r == currRow + 1 && board[r][co] == nullptr)
			return true;

		// Diagonal capture
		if (r == currRow + 1 && abs(co - currCol) == 1 &&
			board[r][co] != nullptr &&
			board[r][co]->getColor() != "black")
			return true;
	}

};



//***********************************
//===========ROCK implementation=====
//***********************************
bool Rook::isValid_Move(int r, int co, Piece* board[8][8])
{
	if (!(r == getRow() || co == getCol()))
		return false;

	int currRow = getRow();
	int currCol = getCol();

	// Moving vertically
	if (co == currCol)
	{
		int step = (r > currRow) ? 1 : -1;
		for (int i = currRow + step; i != r; i += step)
		{
			if (board[i][currCol] != nullptr)
				return false; // path blocked
		}
	}
	// Moving horizontally
	else
	{
		int step = (co > currCol) ? 1 : -1;
		for (int i = currCol + step; i != co; i += step)
		{
			if (board[currRow][i] != nullptr)
				return false; // path blocked
		}
	}

	return true;
}
//***********************************
//===========Knight implementation=====
//***********************************
Knight::Knight(string c, int r, int co, char sym)
	: Piece(c, r, co, 'K')
{
}

bool Knight::isValid_Move(int r, int co, Piece* board[8][8])
{

	int rowDiff = abs(r - getRow());
	int colDiff = abs(co - getCol());
	return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);

}


//***********************************
//===========BISHOP implementation=====
//***********************************
bool Bishop::isValid_Move(int r, int co, Piece* board[8][8])
{
	if (abs(r - getRow()) != abs(co - getCol()))
		return false;

	int rowStep = (r > getRow()) ? 1 : -1;
	int colStep = (co > getCol()) ? 1 : -1;

	int i = getRow() + rowStep;
	int j = getCol() + colStep;

	while (i != r && j != co)
	{
		if (board[i][j] != nullptr)
			return false; // path blocked

		i += rowStep;
		j += colStep;
	}

	return true;
}
//***********************************
//===========QUEEN implementation=====
//***********************************
bool Queen::isValid_Move(int r, int co, Piece* board[8][8])
{
	int currRow = getRow();
	int currCol = getCol();

	// Rook-like movement
	if (r == currRow || co == currCol)
	{
		int rowStep = (r == currRow) ? 0 : (r > currRow ? 1 : -1);
		int colStep = (co == currCol) ? 0 : (co > currCol ? 1 : -1);

		int i = currRow + rowStep;
		int j = currCol + colStep;

		while (i != r || j != co)
		{
			if (board[i][j] != nullptr)
				return false;

			i += rowStep;
			j += colStep;
		}

		return true;
	}

	// Bishop-like movement
	if (abs(r - currRow) == abs(co - currCol))
	{
		int rowStep = (r > currRow) ? 1 : -1;
		int colStep = (co > currCol) ? 1 : -1;

		int i = currRow + rowStep;
		int j = currCol + colStep;

		while (i != r && j != co)
		{
			if (board[i][j] != nullptr)
				return false;

			i += rowStep;
			j += colStep;
		}

		return true;
	}

	return false;
}
//***********************************
//===========KING implementation=====A
//***********************************

King::King(string c, int r, int co, char sym)
	: Piece(c, r, co, 'K')
{
}
bool King::isValid_Move(int r, int co, Piece* board[8][8])
{
	int rowDiff = abs(r - getRow());
	int colDiff = abs(co - getCol());
	return (rowDiff <= 1 && colDiff <= 1);
}

// Helper function to convert user input like "E2" to row and column indices
void parseInput(string pos, int& row, int& col)
{
	col = toupper(pos[0]) - 'A';   // A-H → 0-7
	int boardRow = pos[1] - '0';   // '1'-'8' → 1-8

	row = 8 - boardRow;            // convert to array index
}
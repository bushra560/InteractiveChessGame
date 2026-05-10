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

		// EN PASSANT (WHITE)
		if (r == currRow - 1 && abs(co - currCol) == 1 && board[r][co] == nullptr)
		{
			if (canEnPassant(board, currRow, currCol, r, co,
				"white",
				lastDoublePawnRow, lastDoublePawnCol,
				lastDoublePawnColor, lastMoveWasDoublePawn))
				return true;
		}
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
	// EN PASSANT (BLACK)
	if (r == currRow + 1 && abs(co - currCol) == 1 && board[r][co] == nullptr)
	{
		if (canEnPassant(board, currRow, currCol, r, co,
			"black",
			lastDoublePawnRow, lastDoublePawnCol,
			lastDoublePawnColor, lastMoveWasDoublePawn))
			return true;
	}


	return false;
};



//***********************************
//===========ROCK implementation=====
//***********************************
Rook::Rook(string c, int r, int co, char sym)
	: Piece(c, r, co, 'R')
{
}
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
	: Piece(c, r, co, 'N')
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
Bishop::Bishop(string c, int r, int co, char sym)
	: Piece(c, r, co, 'B')
{
}
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
Queen::Queen(string c, int r, int co, char sym)
	: Piece(c, r, co, 'Q')
{
}
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
bool isSquareAttacked(int r, int co, const string& kingColor, Piece* board[8][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr && board[i][j]->getColor() != kingColor)
			{
				if (board[i][j]->isValid_Move(r, co, board))
					return true;
			}
		}
	}
	return false;
}

bool King::isValid_Move(int r, int co, Piece* board[8][8]) {
	int currRow = getRow();
	int currCol = getCol();
	int rowDiff = abs(r - currRow);
	int colDiff = abs(co - currCol);

	// Case 1: Standard 1-square move
	if (rowDiff <= 1 && colDiff <= 1) {
		if (r == currRow && co == currCol) return false; // Stayed put
		if (board[r][co] != nullptr && board[r][co]->getColor() == getColor()) return false;
		return true;
	}

	// Case 2: Castling (Exactly 2 squares horizontally)
	if (rowDiff == 0 && colDiff == 2) {
		// Only allow if it's the King's first move (you'll need to check your globals here)
		bool kingMoved = (getColor() == "white") ? whiteKingMoved : blackKingMoved;
		if (kingMoved) return false;

		if (co == 6) // King side
			return canCastleKingSide(board, getColor(), currRow, currCol, kingMoved, false);
		if (co == 2) // Queen side
			return canCastleQueenSide(board, getColor(), currRow, currCol, kingMoved, false);
	}
	if (board[r][co] != nullptr &&
		board[r][co]->getColor() == getColor())
		return false;
	return false;
}

//***********************************
//===========DESTRUCTORS=============
//***********************************

Piece::~Piece() {}

Pawn::~Pawn() {}
Rook::~Rook() {}
Knight::~Knight() {}
Bishop::~Bishop() {}
Queen::~Queen() {}
King::~King() {}

//***********************************
//===========Helper Functions=====
//***********************************

// Helper function to move a piece on the board
void makeMove(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol)
{
	Piece* movingPiece = board[fromRow][fromCol];

	// ================= EN PASSANT =================
	if (dynamic_cast<Pawn*>(movingPiece) &&
		canEnPassant(board, fromRow, fromCol, toRow, toCol,
			movingPiece->getColor(),
			lastDoublePawnRow, lastDoublePawnCol,
			lastDoublePawnColor, lastMoveWasDoublePawn))
	{
		doEnPassant(board, fromRow, fromCol, toRow, toCol, movingPiece->getColor());
	}

	// ================= CASTLING =================
	else if (dynamic_cast<King*>(movingPiece) && abs(toCol - fromCol) == 2)
	{
		if (toCol == 6)
			doCastleKingSide(board, fromRow);
		else if (toCol == 2)
			doCastleQueenSide(board, fromRow);
	}

	// ================= NORMAL MOVE =================
	else
	{
		if (board[toRow][toCol] != nullptr)
			delete board[toRow][toCol];

		board[toRow][toCol] = movingPiece;
		board[fromRow][fromCol] = nullptr;
		board[toRow][toCol]->setPosition(toRow, toCol);
	}

	// ================= TRACK DOUBLE PAWN MOVE =================
	if (dynamic_cast<Pawn*>(movingPiece) && abs(toRow - fromRow) == 2)
	{
		lastMoveWasDoublePawn = true;
		lastDoublePawnRow = toRow;
		lastDoublePawnCol = toCol;
		lastDoublePawnColor = movingPiece->getColor();
	}
	else
	{
		lastMoveWasDoublePawn = false;
	}

	// ================= PROMOTION =================
	if (canPromote(board, toRow, toCol))
	{
		char choice;
		cout << "Promote to (Q/R/B/N): ";
		cin >> choice;

		promotePawn(board, toRow, toCol, choice, movingPiece->getColor());
	}
}
//================ Helper function to convert user input like "E2" to row and column indices=============
void parseInput(string pos, int& row, int& col)
{
	col = toupper(pos[0]) - 'A';
	int boardRow = pos[1] - '0';

	row = 8 - boardRow;            // convert to array index
}

//***********************************
//===========Checkmate & InCheck =====
//***********************************
// 1. Find the King's position helper

// To check if a king is in check, we first need to find its position on the board. 
// This function iterates through the board to locate the King of the specified color
// and returns its row and column indices.
void findKing(string color, Piece* board[8][8], int& kRow, int& kCol) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr &&
				board[i][j]->getSymbol() == 'K' &&
				board[i][j]->getColor() == color) {
				kRow = i; kCol = j;
				return;
			}
		}
	}
}

// 2. Check if a specific color's King is currently in check

// To determine if a King is in check, we first find its position using the helper function above,
// and then we check if that square is attacked by any piece of the opposite color using the isSquareAttacked function.
bool isInCheck(string color, Piece* board[8][8]) {
	int kRow, kCol;
	findKing(color, board, kRow, kCol);
	return isSquareAttacked(kRow, kCol, color, board);
}

// 3. Simulate a move to see if it's "Safe" (doesn't result in check)

// To check if a move is safe, we temporarily make the move on the board, check if it leaves the King in check,
// and then undo the move to restore the original board state. This allows us to test potential moves 
// without permanently altering the game state.

bool isMoveSafe(int fromR, int fromC, int toR, int toC, string color, Piece* board[8][8])
{
	Piece* originalSource = board[fromR][fromC];
	Piece* originalDest = board[toR][toC];

	// Temporarily make the move
	board[toR][toC] = originalSource;
	board[fromR][fromC] = nullptr;
	int oldR = originalSource->getRow();
	int oldC = originalSource->getCol();
	originalSource->setPosition(toR, toC);

	bool safe = !isInCheck(color, board);

	// Undo the move
	originalSource->setPosition(oldR, oldC);
	board[fromR][fromC] = originalSource;
	board[toR][toC] = originalDest;

	return safe;
}

// 4. Check if any legal moves exist (to detect Checkmate/Stalemate)
// 
// 	   To determine if a player has any legal moves, we need to iterate through all of their pieces and check if any of them can make a valid move that also keeps the King safe. This involves two filters:
	//Filter 1: Does the piece's movement rule allow it to go there? (isValid_Move)
	//Filter 2: If yes, does making that move keep the King safe ? (isMoveSafe)
bool hasLegalMoves(string color, Piece* board[8][8]) {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board[r][c] != nullptr && board[r][c]->getColor() == color) {
				// Try moving this piece to every possible square on the board
				for (int toR = 0; toR < 8; toR++) {
					for (int toC = 0; toC < 8; toC++) {
						if (board[r][c]->isValid_Move(toR, toC, board)) {
							// If piece-rule says okay, check if it leaves King safe
							if (isMoveSafe(r, c, toR, toC, color, board)) {
								return true; // Found at least one legal move!
							}
						}
					}
				}
			}
		}
	}
	return false;
}


//***********************************
//=========== Draw Function =====
//***********************************

// 1. Check for Insufficient Material Draw

// Insufficient material occurs when neither player has enough pieces left to force a checkmate.
// ----------------------------------------------------------------------------------------------
//Game is a draw if both players only have their kings left, or if one player has just a king and a minor piece (bishop or knight) while the other player has only a king.
// Dead draws include scenarios like
// King vs King,
// King + Bishop vs King,
// King + Knight vs King,
// King + Bishop vs King + Bishop 
//-----------------------------------------------------------------------------------------------
//Game on if it's 
// King + Rook vs King, 
// King + Queen vs King, 
// or any scenario where a pawn is still on the board (since pawns can promote to queens).
//-----------------------------------------------------------------------------------------------
bool hasInsufficientMaterial(Piece* board[8][8]) {
	int whitePieces = 0, blackPieces = 0;
	bool whiteMinor = false, blackMinor = false;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) {
				char sym = toupper(board[i][j]->getSymbol());

				// If there's a Queen, Rook, or Pawn on the board, checkmate is still possible
				if (sym == 'Q' || sym == 'R' || sym == 'P') return false;

				if (board[i][j]->getColor() == "white") {
					whitePieces++;
					if (sym == 'B' || sym == 'N') whiteMinor = true;
				}
				else {
					blackPieces++;
					if (sym == 'B' || sym == 'N') blackMinor = true;
				}
			}
		}
	}

	// Draw scenarios:
	// King vs King (1 piece each)
	if (whitePieces == 1 && blackPieces == 1) return true;

	// King + Minor Piece (Knight/Bishop) vs King
	if (whitePieces == 2 && blackPieces == 1 && whiteMinor) return true;
	if (whitePieces == 1 && blackPieces == 2 && blackMinor) return true;

	// King + Minor vs King + Minor
	if (whitePieces == 2 && blackPieces == 2 && whiteMinor && blackMinor) return true;

	return false;
}

// 2. Clean Stalemate Check

// Stalemate occurs when the player to move is not in check but has no legal moves available.
bool isStalemate(string color, Piece* board[8][8]) {
	// Stalemate happens if
	// 1. you are NOT in check
	// 2. you have NO legal moves
	return !isInCheck(color, board) && !hasLegalMoves(color, board);
}
#include "piece.h"

// ======================= EN PASSANT =======================

//EnPassent mean capturing a pawn that has just moved two squares forward from its starting position, as if it had only moved one square. 
// This special move can only be performed immediately after the opponent's pawn makes the double-step move, 
// and it must be done on the very next turn. If the player does not capture en passant immediately, they lose the opportunity to do so.
// This function checks if en passant move is possible
bool canEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol,
	const string& turn,
	int lastDoublePawnRow, int lastDoublePawnCol,
	const string& lastDoublePawnColor, bool lastMoveWasDoublePawn)
{
	// If last move was NOT a double pawn move → cannot do en passant
	if (!lastMoveWasDoublePawn) return false;

	// If last pawn belongs to same player → cannot capture own pawn
	if (lastDoublePawnColor == turn) return false;

	// Ensure current piece is actually a pawn
	if (dynamic_cast<Pawn*>(board[fromRow][fromCol]) == nullptr) return false;

	// For WHITE pawn (moves upward)
	if (turn == "white")
		return (
			toRow == fromRow - 1 &&              // moving one step forward
			abs(toCol - fromCol) == 1 &&         // moving diagonally
			board[toRow][toCol] == nullptr &&    // destination must be empty
			lastDoublePawnRow == fromRow &&      // enemy pawn must be beside current pawn
			lastDoublePawnCol == toCol           // column matches where we move
			);

	// For BLACK pawn (moves downward)
	return (
		toRow == fromRow + 1 &&
		abs(toCol - fromCol) == 1 &&
		board[toRow][toCol] == nullptr &&
		lastDoublePawnRow == fromRow &&
		lastDoublePawnCol == toCol
		);
}

// This function performs the en passant capture
void doEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol, const string& turn)
{
	int capRow = (turn == "white") ? toRow + 1 : toRow - 1;

	// Delete captured pawn
	delete board[capRow][toCol];
	board[capRow][toCol] = nullptr;

	// Move current pawn
	Piece* pawn = board[fromRow][fromCol];
	board[toRow][toCol] = pawn;
	board[fromRow][fromCol] = nullptr;
	pawn->setPosition(toRow, toCol);
}

// ======================= CASTLING =======================

//CastleKingSide means swapping the king with the rook on the kingside (right side of the board for white, left side for black).
//Rule is there should be nothing im between the king and rook, neither the king nor the rook should have moved before,
// and the squares the king moves through must not be under attack.
// Check if king-side castling is allowed
bool canCastleKingSide(Piece* board[8][8], const string& color, int row, int col,
	bool kingMoved, bool rookMoved)
{
	// King or rook already moved → not allowed
	if (kingMoved || rookMoved) return false;

	// No king at position → invalid
	if (board[row][col] == nullptr) return false;

	// Ensure correct color king
	if (board[row][col]->getColor() != color) return false;

	// King cannot be in check
	if (isSquareAttacked(row, col, color, board)) return false;

	// Squares between king and rook must be empty
	if (board[row][col + 1] != nullptr) return false;
	if (board[row][col + 2] != nullptr) return false;

	// Squares king passes through must not be attacked
	if (isSquareAttacked(row, col + 1, color, board)) return false;
	if (isSquareAttacked(row, col + 2, color, board)) return false;

	return true; // All conditions satisfied
}

//CastleQueenSide means swapping the king with the rook on the queenside (left side of the board for white, right side for black).
//Rule is there should be nothing im between the king and rook, neither the king nor the rook should have moved before,
// and the squares the king moves through must not be under attack.
// Check if queen-side castling is allowed
bool canCastleQueenSide(Piece* board[8][8], const string& color, int row, int col,
	bool kingMoved, bool rookMoved)
{
	if (kingMoved || rookMoved) return false;

	if (board[row][col] == nullptr) return false;

	if (board[row][col]->getColor() != color) return false;

	if (isSquareAttacked(row, col, color, board)) return false;

	// Check all squares between king and rook (3 squares here)
	if (board[row][col - 1] != nullptr) return false;
	if (board[row][col - 2] != nullptr) return false;
	if (board[row][col - 3] != nullptr) return false;

	// Squares king moves through must be safe
	if (isSquareAttacked(row, col - 1, color, board)) return false;
	if (isSquareAttacked(row, col - 2, color, board)) return false;

	return true;
}

// Perform king-side castling
void doCastleKingSide(Piece* board[8][8], int row)
{
	// Move king from column 4 → 6
	board[row][6] = board[row][4];

	// Move rook from column 7 → 5
	board[row][5] = board[row][7];

	// Clear old positions
	board[row][4] = nullptr;
	board[row][7] = nullptr;

	// Update positions
	board[row][6]->setPosition(row, 6);
	board[row][5]->setPosition(row, 5);
}

// Perform queen-side castling
void doCastleQueenSide(Piece* board[8][8], int row)
{
	// Move king from column 4 → 2
	board[row][2] = board[row][4];

	// Move rook from column 0 → 3
	board[row][3] = board[row][0];

	// Clear old positions
	board[row][4] = nullptr;
	board[row][0] = nullptr;

	// Update positions
	board[row][2]->setPosition(row, 2);
	board[row][3]->setPosition(row, 3);
}


// ======================= PROMOTION =======================

// Check if pawn reached last rank
bool canPromote(Piece* board[8][8], int row, int col)
{
	// No piece → cannot promote
	if (board[row][col] == nullptr) return false;

	// Only pawn can promote
	if (dynamic_cast<Pawn*>(board[row][col]) == nullptr) return false;

	// White pawn reached top
	if (board[row][col]->getColor() == "white" && row == 0) return true;

	// Black pawn reached bottom
	if (board[row][col]->getColor() == "black" && row == 7) return true;

	return false;
}

// Promotion basically means when a pawn reaches the opposite end of the board, it can be promoted to any other piece (except a king).
// Replace pawn with selected piece
void promotePawn(Piece* board[8][8], int row, int col, char choice, const string& color)
{
	// Remove pawn
	delete board[row][col];

	// Replace with chosen piece
	if (choice == 'Q' || choice == 'q')
		board[row][col] = new Queen(color, row, col, 'Q');

	else if (choice == 'R' || choice == 'r')
		board[row][col] = new Rook(color, row, col, 'R');

	else if (choice == 'B' || choice == 'b')
		board[row][col] = new Bishop(color, row, col, 'B');

	else // default → Knight
		board[row][col] = new Knight(color, row, col, 'N');
}
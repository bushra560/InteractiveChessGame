#include"piece.h"  

//EnPassent mean capturing a pawn that has just moved two squares forward from its starting position, as if it had only moved one square. 
// This special move can only be performed immediately after the opponent's pawn makes the double-step move, 
// and it must be done on the very next turn. If the player does not capture en passant immediately, they lose the opportunity to do so.

bool canEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol,
    const string& turn,
    int lastDoublePawnRow, int lastDoublePawnCol,
    const string& lastDoublePawnColor, bool lastMoveWasDoublePawn)
{
    if (!lastMoveWasDoublePawn) return false;
    if (lastDoublePawnColor == turn) return false;
    if (dynamic_cast<Pawn*>(board[fromRow][fromCol]) == nullptr) return false;

    if (turn == "white")
        return (toRow == fromRow - 1 && abs(toCol - fromCol) == 1 &&
            board[toRow][toCol] == nullptr &&
            lastDoublePawnRow == fromRow && lastDoublePawnCol == toCol);

    return (toRow == fromRow + 1 && abs(toCol - fromCol) == 1 &&
        board[toRow][toCol] == nullptr &&
        lastDoublePawnRow == fromRow && lastDoublePawnCol == toCol);
}

void doEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol,
    const string& turn)
{
    int capRow = (turn == "white") ? toRow + 1 : toRow - 1;
    delete board[capRow][toCol];
    board[capRow][toCol] = nullptr;
    makeMove(board, fromRow, fromCol, toRow, toCol);
}
//CastleKingSide means swapping the king with the rook on the kingside (right side of the board for white, left side for black).
//Rule is there should be nothing im between the king and rook, neither the king nor the rook should have moved before,
// and the squares the king moves through must not be under attack.

bool canCastleKingSide(Piece* board[8][8], const string& color, int row, int col,
    bool kingMoved, bool rookMoved)
{
    if (kingMoved || rookMoved) return false;
    if (board[row][col] == nullptr) return false;
    if (board[row][col]->getColor() != color) return false;
    if (isSquareAttacked(row, col, color, board)) return false;
    if (board[row][col + 1] != nullptr) return false;
    if (board[row][col + 2] != nullptr) return false;
    if (isSquareAttacked(row, col + 1, color, board)) return false;
    if (isSquareAttacked(row, col + 2, color, board)) return false;
    return true;
}
//CastleQueenSide means swapping the king with the rook on the queenside (left side of the board for white, right side for black).
//Rule is there should be nothing im between the king and rook, neither the king nor the rook should have moved before,
// and the squares the king moves through must not be under attack.
bool canCastleQueenSide(Piece* board[8][8], const string& color, int row, int col,
    bool kingMoved, bool rookMoved)
{
    if (kingMoved || rookMoved) return false;
    if (board[row][col] == nullptr) return false;
    if (board[row][col]->getColor() != color) return false;
    if (isSquareAttacked(row, col, color, board)) return false;
    if (board[row][col - 1] != nullptr) return false;
    if (board[row][col - 2] != nullptr) return false;
    if (board[row][col - 3] != nullptr) return false;
    if (isSquareAttacked(row, col - 1, color, board)) return false;
    if (isSquareAttacked(row, col - 2, color, board)) return false;
    return true;
}

void doCastleKingSide(Piece* board[8][8], int row)
{
    board[row][6] = board[row][4];
    board[row][5] = board[row][7];
    board[row][4] = nullptr;
    board[row][7] = nullptr;
    board[row][6]->setPosition(row, 6);
    board[row][5]->setPosition(row, 5);
}

void doCastleQueenSide(Piece* board[8][8], int row)
{
    board[row][2] = board[row][4];
    board[row][3] = board[row][0];
    board[row][4] = nullptr;
    board[row][0] = nullptr;
    board[row][2]->setPosition(row, 2);
    board[row][3]->setPosition(row, 3);
}

bool canPromote(Piece* board[8][8], int row, int col)
{
    if (board[row][col] == nullptr) return false;
    if (dynamic_cast<Pawn*>(board[row][col]) == nullptr) return false;

    if (board[row][col]->getColor() == "white" && row == 0) return true;
    if (board[row][col]->getColor() == "black" && row == 7) return true;

    return false;
}

void promotePawn(Piece* board[8][8], int row, int col, char choice, const string& color)
{
    delete board[row][col];

    if (choice == 'Q' || choice == 'q')
        board[row][col] = new Queen(color, row, col, 'Q');
    else if (choice == 'R' || choice == 'r')
        board[row][col] = new Rook(color, row, col, 'R');
    else if (choice == 'B' || choice == 'b')
        board[row][col] = new Bishop(color, row, col, 'B');
    else
        board[row][col] = new Knight(color, row, col, 'N');
}
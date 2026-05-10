//
//#include "piece.h"
//
//// ======================= EN PASSANT =======================
//
////EnPassent mean capturing a pawn that has just moved two squares forward from its starting position, as if it had only moved one square. 
//// This special move can only be performed immediately after the opponent's pawn makes the double-step move, 
//// and it must be done on the very next turn. If the player does not capture en passant immediately, they lose the opportunity to do so.
//// This function checks if en passant move is possible
//bool canEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol,
//    const string& turn,
//    int lastDoublePawnRow, int lastDoublePawnCol,
//    const string& lastDoublePawnColor, bool lastMoveWasDoublePawn)
//{
//    // If last move was NOT a double pawn move → cannot do en passant
//    if (!lastMoveWasDoublePawn) return false;
//
//    // If last pawn belongs to same player → cannot capture own pawn
//    if (lastDoublePawnColor == turn) return false;
//
//    // Ensure current piece is actually a pawn
//    if (dynamic_cast<Pawn*>(board[fromRow][fromCol]) == nullptr) return false;
//
//    // For WHITE pawn (moves upward)
//    if (turn == "white")
//        return (
//            toRow == fromRow - 1 &&              // moving one step forward
//            abs(toCol - fromCol) == 1 &&         // moving diagonally
//            board[toRow][toCol] == nullptr &&    // destination must be empty
//            lastDoublePawnRow == fromRow &&      // enemy pawn must be beside current pawn
//            lastDoublePawnCol == toCol           // column matches where we move
//            );
//
//    // For BLACK pawn (moves downward)
//    return (
//        toRow == fromRow + 1 &&
//        abs(toCol - fromCol) == 1 &&
//        board[toRow][toCol] == nullptr &&
//        lastDoublePawnRow == fromRow &&
//        lastDoublePawnCol == toCol
//        );
//}
//
//// This function performs the en passant capture
//void doEnPassant(Piece* board[8][8], int fromRow, int fromCol, int toRow, int toCol, const string& turn)
//{
//    int capRow = (turn == "white") ? toRow + 1 : toRow - 1;
//
//    // Delete captured pawn
//    delete board[capRow][toCol];
//    board[capRow][toCol] = nullptr;
//
//    // Move current pawn
//    Piece* pawn = board[fromRow][fromCol];
//    board[toRow][toCol] = pawn;
//    board[fromRow][fromCol] = nullptr;
//    pawn->setPosition(toRow, toCol);
//}
//
//// ======================= CASTLING =======================
//
////CastleKingSide means swapping the king with the rook on the kingside (right side of the board for white, left side for black).
////Rule is there should be nothing im between the king and rook, neither the king nor the rook should have moved before,
//// and the squares the king moves through must not be under attack.
//// Check if king-side castling is allowed
//bool canCastleKingSide(Piece* board[8][8], const string& color, int row, int col,
//    bool kingMoved, bool rookMoved)
//{
//    // King or rook already moved → not allowed
//    if (kingMoved || rookMoved) return false;
//
//    // No king at position → invalid
//    if (board[row][col] == nullptr) return false;
//
//    // Ensure correct color king
//    if (board[row][col]->getColor() != color) return false;
//
//    // King cannot be in check
//    if (isSquareAttacked(row, col, color, board)) return false;
//
//    // Squares between king and rook must be empty
//    if (board[row][col + 1] != nullptr) return false;
//    if (board[row][col + 2] != nullptr) return false;
//
//    // Squares king passes through must not be attacked
//    if (isSquareAttacked(row, col + 1, color, board)) return false;
//    if (isSquareAttacked(row, col + 2, color, board)) return false;
//
//    return true; // All conditions satisfied
//}
//
////CastleQueenSide means swapping the king with the rook on the queenside (left side of the board for white, right side for black).
////Rule is there should be nothing im between the king and rook, neither the king nor the rook should have moved before,
//// and the squares the king moves through must not be under attack.
//// Check if queen-side castling is allowed
//bool canCastleQueenSide(Piece* board[8][8], const string& color, int row, int col,
//    bool kingMoved, bool rookMoved)
//{
//    if (kingMoved || rookMoved) return false;
//
//    if (board[row][col] == nullptr) return false;
//
//    if (board[row][col]->getColor() != color) return false;
//
//    if (isSquareAttacked(row, col, color, board)) return false;
//
//    // Check all squares between king and rook (3 squares here)
//    if (board[row][col - 1] != nullptr) return false;
//    if (board[row][col - 2] != nullptr) return false;
//    if (board[row][col - 3] != nullptr) return false;
//
//    // Squares king moves through must be safe
//    if (isSquareAttacked(row, col - 1, color, board)) return false;
//    if (isSquareAttacked(row, col - 2, color, board)) return false;
//
//    return true;
//}
//
//// Perform king-side castling
//void doCastleKingSide(Piece* board[8][8], int row)
//{
//    // Move king from column 4 → 6
//    board[row][6] = board[row][4];
//
//    // Move rook from column 7 → 5
//    board[row][5] = board[row][7];
//
//    // Clear old positions
//    board[row][4] = nullptr;
//    board[row][7] = nullptr;
//
//    // Update positions
//    board[row][6]->setPosition(row, 6);
//    board[row][5]->setPosition(row, 5);
//}
//
//// Perform queen-side castling
//void doCastleQueenSide(Piece* board[8][8], int row)
//{
//    // Move king from column 4 → 2
//    board[row][2] = board[row][4];
//
//    // Move rook from column 0 → 3
//    board[row][3] = board[row][0];
//
//    // Clear old positions
//    board[row][4] = nullptr;
//    board[row][0] = nullptr;
//
//    // Update positions
//    board[row][2]->setPosition(row, 2);
//    board[row][3]->setPosition(row, 3);
//}
//
//
//// ======================= PROMOTION =======================
//
//// Check if pawn reached last rank
//bool canPromote(Piece* board[8][8], int row, int col)
//{
//    // No piece → cannot promote
//    if (board[row][col] == nullptr) return false;
//
//    // Only pawn can promote
//    if (dynamic_cast<Pawn*>(board[row][col]) == nullptr) return false;
//
//    // White pawn reached top
//    if (board[row][col]->getColor() == "white" && row == 0) return true;
//
//    // Black pawn reached bottom
//    if (board[row][col]->getColor() == "black" && row == 7) return true;
//
//    return false;
//}
//
//// Promotion basically means when a pawn reaches the opposite end of the board, it can be promoted to any other piece (except a king).
//// Replace pawn with selected piece
//void promotePawn(Piece* board[8][8], int row, int col, char choice, const string& color)
//{
//    // Remove pawn
//    delete board[row][col];
//
//    // Replace with chosen piece
//    if (choice == 'Q' || choice == 'q')
//        board[row][col] = new Queen(color, row, col, 'Q');
//
//    else if (choice == 'R' || choice == 'r')
//        board[row][col] = new Rook(color, row, col, 'R');
//
//    else if (choice == 'B' || choice == 'b')
//        board[row][col] = new Bishop(color, row, col, 'B');
//
//    else // default → Knight
//        board[row][col] = new Knight(color, row, col, 'N');
//}
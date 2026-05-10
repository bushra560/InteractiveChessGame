#include "piece.h"//including header file
// ================= GLOBAL VARIABLES (for special moves) =================
int lastDoublePawnRow = -1;
int lastDoublePawnCol = -1;
string lastDoublePawnColor = "";
bool lastMoveWasDoublePawn = false;
// Track castling rights
bool whiteKingMoved = false;
bool blackKingMoved = false;
bool whiteRookAMoved = false; // queenside rook
bool whiteRookHMoved = false; // kingside rook
bool blackRookAMoved = false;
bool blackRookHMoved = false;

int halfMoveClock = 0;// counts moves for the 50-move draw rule
// ================= MENU FUNCTIONS =================

void showTitle()
{
    cout << "====================================" << endl;
    cout << "           OOP CHESS GAME          " << endl;
    cout << "====================================" << endl;
}

void showRules()
{
    system("cls");

    cout << "=========== CHESS RULES ===========" << endl;

    cout << "1. White moves first." << endl;
    cout << "2. Pawns move forward only." << endl;
    cout << "3. Rooks move horizontally/vertically." << endl;
    cout << "4. Bishops move diagonally." << endl;
    cout << "5. Knights move in L shape." << endl;
    cout << "6. Queen moves in all directions." << endl;
    cout << "7. King moves one square." << endl;
    cout << "8. Castling is a special king move." << endl;
    cout << "9. En Passant is special pawn capture." << endl;
    cout << "10. Pawn promotion happens at last row." << endl;
    cout << "11. Checkmate wins the game." << endl;

    cout << "\nPress any key to return..." << endl;
    system("pause");
}

void aboutProject()
{
    system("cls");

    cout << "=========== PROJECT INFO ===========" << endl;

    cout << "This project demonstrates:" << endl;
    cout << "- Encapsulation" << endl;
    cout << "- Inheritance" << endl;
    cout << "- Polymorphism" << endl;
    cout << "- Composition" << endl;

    cout << "\nSpecial Features:" << endl;
    cout << "- Castling" << endl;
    cout << "- En Passant" << endl;
    cout << "- Pawn Promotion" << endl;
    cout << "- Checkmate Detection" << endl;
    cout << "- Stalemate Detection" << endl;

    cout << "\nPress any key to return..." << endl;
    system("pause");
}
int main()
{
    int choice;

    while (true)
    {
        system("cls");

        // ================= MAIN MENU =================

        showTitle();

        cout << "1. Start Game" << endl;
        cout << "2. Project Info" << endl;
        cout << "3. Chess Game Rules" << endl;
        cout << "4. Exit" << endl;

        cout << "\nEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            Piece* board[8][8] = { nullptr };

            for (int i = 0; i < 8; i++) {
                board[1][i] = new Pawn("black", 1, i, 'P');
                board[6][i] = new Pawn("white", 6, i, 'P');
            }

            board[0][0] = new Rook("black", 0, 0, 'R');
            board[0][7] = new Rook("black", 0, 7, 'R');
            board[7][0] = new Rook("white", 7, 0, 'R');
            board[7][7] = new Rook("white", 7, 7, 'R');

            board[0][1] = new Knight("black", 0, 1, 'N');
            board[0][6] = new Knight("black", 0, 6, 'N');
            board[7][1] = new Knight("white", 7, 1, 'N');
            board[7][6] = new Knight("white", 7, 6, 'N');

            board[0][2] = new Bishop("black", 0, 2, 'B');
            board[0][5] = new Bishop("black", 0, 5, 'B');
            board[7][2] = new Bishop("white", 7, 2, 'B');
            board[7][5] = new Bishop("white", 7, 5, 'B');

            board[0][3] = new Queen("black", 0, 3, 'Q');
            board[7][3] = new Queen("white", 7, 3, 'Q');

            board[0][4] = new King("black", 0, 4, 'K');
            board[7][4] = new King("white", 7, 4, 'K');

            string turn = "white";

            while (true)
            {
                system("cls");
                //==================== CHECK FOR GAME END CONDITIONS ====================

                // 1. Checkmate Check
                if (isInCheck(turn, board) && !hasLegalMoves(turn, board)) {
                    cout << "\nCHECKMATE! " << (turn == "white" ? "Black" : "White") << " wins!" << endl;
                    break;
                }

                // 2. Stalemate Check
                if (isStalemate(turn, board)) {
                    cout << "\nSTALEMATE! Game is a draw. " << turn << " has no legal moves." << endl;
                    break;
                }

                // 3. Insufficient Material Check
                if (hasInsufficientMaterial(board)) {
                    cout << "\nDRAW! Insufficient material to force a checkmate." << endl;
                    break;
                }

                // 4. 50-Move Rule Check (100 half-moves)
                if (halfMoveClock >= 100) {
                    cout << "\nDRAW! 50 consecutive moves without a capture or pawn push." << endl;
                    break;
                }

                //==================================================================================
                cout << "\nCurrent Turn: " << turn << endl;

                if (isInCheck(turn, board)) {
                    cout << "!!! WARNING: YOU ARE IN CHECK !!!" << endl;
                }

                //==================== DISPLAY BOARD ====================
                cout << "\n   A B C D E F G H" << endl;
                cout << "  -----------------" << endl;

                for (int i = 0; i < 8; i++) {
                    cout << 8 - i << " |";
                    for (int j = 0; j < 8; j++) {
                        if (board[i][j] != nullptr)
                            cout << board[i][j]->getSymbol() << " ";
                        else
                            cout << ". ";
                    }
                    cout << "| " << 8 - i << endl;
                }

                cout << "  -----------------" << endl;
                cout << "   A B C D E F G H\n" << endl;

                int fromRow, fromCol, toRow, toCol;
                string from, to;
                cout << "Example input: E2 E4" << endl;
                cout << "Type MENU to return to Main Menu" << endl;

                cout << "Enter FROM position (e.g., C2): ";
                cin >> from;

                // ================= RETURN TO MENU =================

                if (from == "MENU" || from == "menu")
                {
                    break;
                }
                cout << "Enter TO position (e.g., C3): ";
                cin >> to;
                //******************************
                // PHASE 3 start HERE
                //==input Validation====
                if (from.empty() || to.empty())
                {
                    cout << "Empty input is not allowed!" << endl;
                    system("pause");
                    continue;
                }
                if (from.length() != 2 || to.length() != 2)
                    //for example it is like E23? then 
                {
                    cout << "Invalid input format! Use format like E2" << endl;
                    system("pause");
                    continue;
                }
                //NOW CHECK COLOUMNS
                if (toupper(from[0]) < 'A' || toupper(from[0]) > 'H' ||
                    toupper(to[0]) < 'A' || toupper(to[0]) > 'H')
                {
                    cout << "Invalid column! Use A to H" << endl;
                    system("pause");
                    continue;
                }
                //Now Row CHECK
                if (from[1] < '1' || from[1]>'8' || to[1] < '1' || to[1]>'8')
                {
                    cout << "invalid Row ! use 1 to 8 " << endl;
                    system("pause");
                    continue;
                }

                parseInput(from, fromRow, fromCol);
                parseInput(to, toRow, toCol);
                //********************* SAME POSTON CASE
                // // ===== SAME POSITION CHECK =====
                if (fromRow == toRow && fromCol == toCol)
                {
                    cout << "Invalid move: Source and destination are same!" << endl;
                    system("pause");
                    continue;
                }
                // ===== INPUT VALIDATION ERROR =====
                if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
                    toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
                {
                    cout << "Invalid input!" << endl;
                    system("pause");
                    continue;
                }

                // ===== NO PIECE ERROR =====
                if (board[fromRow][fromCol] == nullptr)
                {
                    cout << "Invalid move: No piece at this position!" << endl;
                    system("pause");
                    continue;
                }

                // ===== TURN ERROR =====
                if (board[fromRow][fromCol]->getColor() != turn)
                {
                    cout << "Not Your Turn" << endl;
                    system("pause");   // ADDED
                    continue;
                }

                // ===== MOVE VALIDATION =====
                if (board[fromRow][fromCol]->isValid_Move(toRow, toCol, board))
                {
                    if (board[toRow][toCol] == nullptr)
                    {
                        board[toRow][toCol] = board[fromRow][fromCol];
                        board[fromRow][fromCol] = nullptr;
                        board[toRow][toCol]->setPosition(toRow, toCol);

                        turn = (turn == "white") ? "black" : "white";
                        continue;
                    }
                    else
                    {
                        if (board[toRow][toCol]->getColor() == turn)
                        {
                            cout << "Move rejected: same team piece" << endl;
                            system("pause");
                            continue;
                        }
                        else
                        {
                            board[toRow][toCol] = board[fromRow][fromCol];
                            board[fromRow][fromCol] = nullptr;
                            board[toRow][toCol]->setPosition(toRow, toCol);

                            turn = (turn == "white") ? "black" : "white";
                            continue;
                        }
                    }
                }
                else
                {
                    cout << "Invalid move according to piece rules!" << endl;
                    system("pause");
                }
            }

            for (int i = 0; i < 8; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    if (board[i][j] != nullptr)
                    {
                        delete board[i][j];
                        board[i][j] = nullptr;
                    }
                }
            }
        }


        // ================= PROJECT INFO =================

        else if (choice == 2)
        {
            aboutProject();
        }

        // ================= RULES =================

        else if (choice == 3)
        {
            showRules();
        }

        // ================= EXIT =================

        else if (choice == 4)
        {
            cout << "\nThank You For Playing!" << endl;
            break;
        }

        else
        {
            cout << "Invalid Choice!" << endl;
            system("pause");
        }
    }
    cout << "\nGame Closed Successfully!" << endl;

    system("pause");
    return 0;
}
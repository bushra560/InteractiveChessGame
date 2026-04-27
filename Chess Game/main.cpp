#include "piece.h"//including header file

int main()
{
    // we will be creating an 8x8 matrix that is initially empty
    Piece* board[8][8] = { nullptr };

    //After creating the space the chess pieces place & positions will be added through array of pointers 
    // creating dynamic memory and intializing the pawns 
    // Giving the position info and appearence of the piece 
    for (int i = 0; i < 8; i++) {
        board[1][i] = new Pawn("black", 1, i, 'P');
        board[6][i] = new Pawn("white", 6, i, 'P');
    }

    // creating dynamic memory and intializing the Rooks
    // Giving the position info and appearence of the piece 
    board[0][0] = new Rook("black", 0, 0, 'R');
    board[0][7] = new Rook("black", 0, 7, 'R');
    board[7][0] = new Rook("white", 7, 0, 'R');
    board[7][7] = new Rook("white", 7, 7, 'R');

    // creating dynamic memory and intializing the Knights
    // Giving the position info and appearence of the piece 
    board[0][1] = new Knight("black", 0, 1, 'N');
    board[0][6] = new Knight("black", 0, 6, 'N');
    board[7][1] = new Knight("white", 7, 1, 'N');
    board[7][6] = new Knight("white", 7, 6, 'N');

    // creating dynamic memory and intializing the Bishop
    // Giving the position info and appearence of the piece 
    board[0][2] = new Bishop("black", 0, 2, 'B');
    board[0][5] = new Bishop("black", 0, 5, 'B');
    board[7][2] = new Bishop("white", 7, 2, 'B');
    board[7][5] = new Bishop("white", 7, 5, 'B');

    // creating dynamic memory and intializing the Queens
    // Giving the position info and appearence of the piece 
    board[0][3] = new Queen("black", 0, 3, 'Q');
    board[7][3] = new Queen("white", 7, 3, 'Q');

    // creating dynamic memory and intializing the Kings
    // Giving the position info and appearence of the piece 
    board[0][4] = new King("black", 0, 4, 'K');
    board[7][4] = new King("white", 7, 4, 'K');

    // now we are arranging pattern to show the chess board on console 
    //info already saved in memory and in Matrix of 8x8
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
    cout << "   A B C D E F G H" << endl;

    string turn = "white";//Turn variable
    while (true)
    {
        // STEP 1: Variables for move
        int fromRow, fromCol;  
        int toRow, toCol;      

        string from, to; // source position (where piece is)
        // destination position (where to move)
        cout << "Enter FROM position (e.g., C2): ";
        cin >> from;

        cout << "Enter TO position (e.g., C3): ";
        cin >> to;

       

        parseInput(from, fromRow, fromCol);
        parseInput(to, toRow, toCol);
        // Validate input format

        if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
            toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8)
        {
            cout << "Invalid input!" << endl;
            continue;
        }
        //Check source validity
        // If there is no piece at selected position
        if (board[fromRow][fromCol] == nullptr)
        {
            cout << "Invalid move: No piece at this position!" << endl;

            // skip this iteration and ask again
            continue;
        }


        // Next steps will go here
        // - Check turn (white/black)

        if ((board[fromRow][fromCol]->getColor()) == turn)
        {
            cout << "Ok " << endl;

        }
        else
        {
            cout << "Not Your Turn " << endl;
            //RULE : Only white pieces move when turn is white, same for black”
            continue;//skip this iteration , go back to input
        }
        // - Check valid move using isValid_Move()
        if (board[fromRow][fromCol]->isValid_Move(toRow, toCol, board))            // Move Validation
            //passing destination Row and Columns
        {
            // - Check destination cell
            if (board[toRow][toCol] == nullptr)
            {
                // EMPTY CELL = normal move
                /*  Move piece pointer
                    Take piece from source
                    Put it in destination*/
                board[toRow][toCol] = board[fromRow][fromCol];

                /*   Clear old square
                     Make source square empty*/
                board[fromRow][fromCol] = nullptr;
                //Update piece position
               // Tell piece its new row / col
                board[toRow][toCol]->setPosition(toRow, toCol);
                // Switch turn
                if (turn == "white")
                    turn = "black";
                else
                    turn = "white";

                continue;//go back for next move
            }
            else
            {
                //Same-color rejection
                if (board[toRow][toCol]->getColor() == turn)
                {
                    cout << "Move is Rejected because it has same team Piece " << endl;
                    continue;//go back to input
                }
                else
                {
                    // CAPTURE CASE (enemy piece)

                                    /* Replace enemy piece with current piece */
                    board[toRow][toCol] = board[fromRow][fromCol];

                    /* Clear old square */
                    board[fromRow][fromCol] = nullptr;

                    // Update position
                    board[toRow][toCol]->setPosition(toRow, toCol);

                    // Switch turn
                    if (turn == "white")
                        turn = "black";
                    else
                        turn = "white";

                    continue;//go back for next move
                }
            }


        }
        else
        {
            cout << "Invalid Move according to piece rules!" << endl;
        }

        // - Move piece
    }
    // Freeing memory of the 8x8 Matrix
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            //Best Practice to check that if it is null or occupied
            if (board[i][j] != nullptr)
            {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
 
    system("pause");
    return 0;
}
#include <iostream>
#include <vector>
#include <stdlib.h> //used to clear terminal screen each round
using namespace std;

const char null = '.'; const char x = 'X'; const char o = 'O';
const char ongoing = 'n'; //game state = ongoing if no winner yet and board not full

vector<vector<char>> board = {
    {null,null,null},
    {null,null,null},
    {null,null,null},
};
bool IsValid(int row, int col) { //validate user input
    if (row > 0 && row < 4 && col>0 && col < 4 && board[row - 1][col - 1] == null)return 1;
    return 0;
}
void OutputBoard() {
    system("CLS"); //clear previous board from terminal
    cout << "Use format <row><space><column> where row, column are 1-3" << endl;
    cout << "_____________" << endl;
    for (int row = 0;row < 3;row++) {
        for (int col = 0;col < 3;col++) {
            if (col == 2) {
                cout << "| " << board[row][col] << " |";
            }
            else {
                cout << "| " << board[row][col] << " ";
            }
        }
        cout << endl;
        if (row == 2) {
            cout << "|___|___|___|" << endl;

        }
        else {
            cout << "|---|---|---|" << endl;
        }
    }
};
char GameState() {
    // returns "X" if x won and "O" if o won 
    // returns "n" if there's no winner and board still has empty spots
    // returns "d" if draw 
    char player[2] = { x,o };
    bool HasEmptySpot = 0;

    for (int i = 0;i < 2;i++) {//for each player
        int count[4] = { 0,0,0,0 }; //count along each direction
        for (int r = 0;r < 3;r++) {
            for (int c = 0;c < 3;c++) {
                if (board[r][c] == player[i]) { count[0]++; } //count horizontally
                if (board[c][r] == player[i]) { count[1]++; } //count vertically
                if (r == c && board[r][c] == player[i]) { count[2]++; } //count along - diagonal
                if (r + c == 2 && board[r][c] == player[i]) { count[3]++; }  //count along + diagonal
                if (board[r][c] == null)HasEmptySpot = 1;
            }
            for (int m = 0;m < 4;m++) { if (count[m] == 3)return player[i]; }//return winner if any
            count[0] = 0;count[1] = 0; //reset only for orthogonal directions
        }
    }
    if (HasEmptySpot)return ongoing;
    return 'd'; // draw
}
void UpdateBoard(bool turn, int row, int col) {
    //coordinates have already been validated
    // row n has index n-1 and column k has index k-1
    board[row - 1][col - 1] = (turn == 0) ? o : x;
}

int minimax(int depth, bool maximizingplayer) {
    char result = GameState();
    //if game over
    if (result == x)return 100; 
    if (result == o)return -100;
    if (result == 'd')return 0;

    int MaxEval = -1000; //max score for maximising player
    int MinEval = 1000; //min score for minimising player

    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            if (board[i][j] == null) {
                board[i][j] = maximizingplayer? x:o;
                if (maximizingplayer) {
                       MaxEval = max(MaxEval, minimax(depth+1,0) -depth);
                }
                else {
                      MinEval = min(MinEval, minimax(depth+1, 1) + depth);
                }
                board[i][j] = null;
            }
        }
    }
    return maximizingplayer==1 ? MaxEval : MinEval;
}

void AImove() {
    int p = -1, q = -1; //best move is to play at (p,q)
    int MaxEval = INT_MIN;

    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            if (board[i][j] == null) {//for each possible move

                board[i][j] = x;
                int eval = minimax(0,0); 
                if (eval > MaxEval) {//new best move discovered
                    p = i; q = j;
                    MaxEval = eval;
                }
                board[i][j] = null;

            }
        }
    }
    board[p][q] = x;
}

int main()
{
    bool vsAI = 1;
    bool turnX = 1; // 0 = O first ;  1 = X first
    char state = ongoing;
    int row, col;
    cout << "vs AI? 1 = Yes \n";
    cin >> vsAI;
    cout << "Who starts? 1-x or 0-o  ";
    cin >> turnX;

    if (vsAI) {

        while (state == ongoing) {
            OutputBoard();
            if (turnX == 0) {
                cout << "Your turn" << endl;
                cin >> row >> col;

                while (IsValid(row, col) == 0) {
                    cout << "Invalid coordinates. Enter again." << endl;
                    cin >> row >> col;
                }
                UpdateBoard(0, row, col);

            }
            else {
                AImove();
            }
            state = GameState();
            turnX = !(turnX); //swap turns 
        }

    }
    else {
        while (state == ongoing) {
            OutputBoard();
            cout << ((turnX == 0) ? "O's turn" : "X's turn") << endl;
            cin >> row >> col;

            while (IsValid(row, col) == 0) {
                cout << "Invalid coordinates. Enter again." << endl;
                cin >> row >> col;
            }

            UpdateBoard(turnX, row, col);
            state = GameState();
            turnX = !(turnX); //swap turns 
        }
    }

    OutputBoard();
    cout << ((state == o) ? "Player O has won!" : ((state == x) ? "Player X has won!" : "Draw")) << "\n";
}

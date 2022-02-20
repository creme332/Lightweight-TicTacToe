#include <iostream>
#include <vector>
#include <stdlib.h> //used to clear terminal screen each round
using namespace std;

const char emptyspot = '.'; const char x = 'X'; const char o = 'O';
const char ongoing = 'n'; //game state = ongoing if no winner yet and board not full

vector<vector<char>> board = {
    {emptyspot,emptyspot,emptyspot},
    {emptyspot,emptyspot,emptyspot},
    {emptyspot,emptyspot,emptyspot}
};

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
    // returns "n" if game is ongoing - game has empty spots
    // returns "d" if draw 
    char k[2] = { x,o };
    bool HasEmptySpot = 0;

    for (int i = 0;i < 2;i++) {//for each player
        int count[4] = { 0,0,0,0 }; //count along each direction
        for (int r = 0;r < 3;r++) {
            for (int c = 0;c < 3;c++) {
                if (board[r][c] == k[i]) { count[0]++; } //count horizontally
                if (board[c][r] == k[i]) { count[1]++; } //count vertically
                if (r == c && board[r][c] == k[i]) { count[2]++; } //count along - diagonal
                if (r + c == 2 && board[r][c] == k[i]) { count[3]++; }  //count along + diagonal
                if (board[r][c] == emptyspot)HasEmptySpot = 1;
            }
            for (int m = 0;m < 4;m++) { if (count[m] == 3)return k[i]; }//return winner if any
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
bool IsValid(int row, int col) {
    if (row > 0 && row < 4 && col>0 && col < 4 && board[row - 1][col - 1] == emptyspot)return 1;
    return 0;
}
int minimax(int row, int col, vector<vector<char>> b, int depth, bool maximizingplayer) {
    b[row][col] = (maximizingplayer == 1) ? x : o;
    //(row, col) = previous move

    char result = GameState();

    //if game over
    if (result == 'X')return 100; //our AI, the maximising player
    if (result == 'O')return -100;
    if (result == 'd')return (maximizingplayer == 1) ? 50 : -50;

    if (depth == 0) { //evaluate move
        //first if able to stop opponent from winning, good
        //second, a move is good if player becomes 1 move away from win.
        char k = (maximizingplayer == 1) ? x : o;
        int empty[4] = { 0,0,0,0 };
        int count[4] = { 0,0,0,0 }; //count along each direction

        for (int r = 0;r < 3;r++) {
            for (int c = 0;c < 3;c++) {

                if (r == row || c == col) {
                    if (b[r][c] == k) { count[0]++; } //count horizontally
                    if (b[c][r] == k) { count[1]++; } //count vertically
                    if (r == c && b[r][c] == k) { count[2]++; } //count along - diagonal
                    if (r + c == 2 && b[r][c] == k) { count[3]++; }  //count along + diagonal
                }

            }
            for (int m = 0;m < 4;m++) { if (count[m] == 2 && empty[m] == 1)return (maximizingplayer == 1) ? 75 : -75;}
            count[0] = 0;count[1] = 0; //reset only for orthogonal directions
        }
        return (maximizingplayer == 1) ? 25 : -25; //neutral move

    }


    if (maximizingplayer) {
        int MaxEval = INT_MIN;

        for (int i = 0;i < 3;i++) {
            for (int j = 0;j < 3;j++) {
                if (b[i][j] == emptyspot) {
                    MaxEval = max(MaxEval, minimax(i, j, b, depth - 1, 0));
                }
            }
        }
        return MaxEval;

    }
    else {
        int MinEval = INT_MAX;

        for (int i = 0;i < 3;i++) {
            for (int j = 0;j < 3;j++) {
                if (b[i][j] == emptyspot) {
                    MinEval = min(MinEval, minimax(i, j, b, depth - 1, 1));
                }
            }
        }
        return MinEval;
    }
}

void AImove() {
    int p=-1, q=-1; //best move is to play at (p,q)
    int MaxEval = INT_MIN;

    for (int i = 0;i < 3;i++) {
        for (int j = 0;j < 3;j++) {
            if (board[i][j] == emptyspot) {//for each possible move
                int eval = minimax(i, j, board, 4, 1); //evaluate move 
                if (eval > MaxEval) {//new best move discovered
                    p = i; q = j;
                    MaxEval = eval;
                }
            }
        }
    }
    //play best move
    for (int i = 0;i < 100000000;i++);
    board[p][q] = x;
}

int main()
{
    bool vsAI = 1;
    bool turnX = 1;// 0 - player o  1 - player x
    char state = ongoing;
    int row, col;

    //cout << "vs AI? 1 = Yes \n";
    //cin >> vsAI;
    //cout << "Who starts? 1-x or 0-o  ";
    //cin >> turnX;

    if (vsAI) {
        while (state == ongoing) {
            OutputBoard();
            if (turnX == 0) {
                cout << "O's turn" << endl;
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
    cout << ((state == o) ? "Player O has won!" : ((state == x) ? "Player X has won!" : "Draw")) << endl;
}

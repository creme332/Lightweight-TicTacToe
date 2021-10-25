#define ll long long
#include <iostream>

//#include <utility>
#include <vector>
using namespace std;

const char emptyspot = '.';
const char x = 'X';
const char o = 'O';
const char ongoing = 'n'; //game state = ongoing if no winner yet and board not full

char board[3][3] = { {emptyspot,emptyspot,emptyspot},{emptyspot,emptyspot,emptyspot},{emptyspot,emptyspot,emptyspot} };
void outputboard() {
    cout << endl;
    for (int row = 0;row < 3;row++) {
        for (int col = 0;col < 3;col++) {
            cout << board[row][col] << "     ";
        }
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
    }
};
char winner() { //checks for winner
    // "x" if x won and "o" if o won 
    // "draw" if draw / "ON" if game is ongoing
    int xcount, ocount; //counts number of x and o

    //horizontal check
    xcount = 0;
    ocount = 0;
    for (int row = 0;row < 4;row++) {
        for (int col = 0;col < 4;col++) {
            if (board[row][col] == x) {
                xcount++;
            }
            if (board[row][col] == o) {
                ocount++;
            }
        }
        if (xcount == 3) {
            return x;
        }
        if (ocount == 3) {
            return o;
        }
        xcount = 0;
        ocount = 0;
    }

    //vertical check
    xcount = 0;
    ocount = 0;
    for (int col = 0;col < 4;col++) {
        for (int row = 0;row < 4;row++) {
            if (board[row][col] == x) {
                xcount++;
            }
            if (board[row][col] == o) {
                ocount++;
            }
        }
        if (xcount == 3) {
            return x;
        }
        if (ocount == 3) {
            return o;
        }
        xcount = 0;
        ocount = 0;
    }

    //positive diagonal check
    if (board[2][0] == x && board[1][1] == x && board[0][2] == x) {
        return x;
    }
    if (board[2][0] == o && board[1][1] == o && board[0][2] == o) {
        return o;
    }

    //negative diagonal check 
    if (board[0][0] == x && board[1][1] == x && board[2][2] == x) {
        return x;
    }
    if (board[0][0] == o && board[1][1] == o && board[2][2] == o) {
        return o;
    }
    return ongoing;
}
void updateboard(bool turn, int row, int col) {
    //coordinates are valid
    if (turn == 0) {
        board[row-1][col-1] = o;    // row n has index n-1 and column k has index k-1
    }
    else {
        board[row-1][col-1] = x;
    }
}
bool validatecoordinates(int row, int col) {
    if (row > 0 && row < 4 && col>0 && col < 4 && board[row-1][col-1]==emptyspot)return 1;
    return 0;
}
int main()
{
    bool turnX = 0;// 0 - player o  1 - player x
    char state=ongoing;
    int row, col;
    cout << "Rules :" << endl;
    cout << "Enter row <space> column" << endl;
    cout << "Values of row and column should be between 1 and 3 inclusive" << endl;

    while (state==ongoing) {
        outputboard();
        if (turnX == 0) {
            cout << "O's turn" << endl;
        }
        else {
            cout << "X's turn" << endl;
        }
        cin >> row >> col;

        if (validatecoordinates(row, col) == 0) { //invalid coordinates
            cout << "Invalid coordinates" << endl;
            state = ongoing;
        }
        else { //valid coordinates
            updateboard(turnX, row, col);
            state = winner();
            turnX = !(turnX); //swap turns 
        }
    }

    outputboard();
    if (state == o) {
        cout << "Player O has won!" << endl;
    }
    else {
        if (state == x) {
            cout << "Player X has won!" << endl;

        }
        else {
            cout << "Draw" << endl;
        }
    }
 
}

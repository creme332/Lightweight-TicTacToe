#include <iostream>
using namespace std;

const char emptyspot = '.';
const char x = 'x';
const char o = 'o';


char board[3][3] = { {emptyspot,emptyspot,emptyspot},{emptyspot,emptyspot,emptyspot},{emptyspot,emptyspot,emptyspot} };
void outputboard() {
    cout << endl;
    for (int row = 0;row < 3;row++) {
        for (int col = 0;col < 3;col++) {
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
};
string winner() { //checks for winner
    // "x" if x won and "o" if o won 
    // "draw" if draw / "on" if game is ongoing

    return "";
}
void updateboard(bool turn, int row, int col) {
    if (turn == x) {
        
    }
}
bool validatecoordinates(int row, int col) {
    if (row > 0 && row < 4 && col>0 && col < 4 && board[row][col]==emptyspot)return 1;
    return 0;
}
int main()
{
    bool turnX = 0;// 0 - player o  1 - player x
    string state="on";
    int row, col;
    cout << "Rules :" << endl;
    cout << "Enter row <space> column" << endl;
    cout << "Values of row and column should be between 1 and 3 inclusive" << endl;
    while (state=="on") {
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
            state = "on";
        }
        else {
            updateboard(turnX, row, col);
            state = winner();
        }
    }

    if (state == "O") {
        cout << "Player O has won" << endl;
    }
    else {
        if (state == "X") {
            cout << "Player X has won" << endl;

        }
        else {
            cout << "Draw" << endl;
        }
    }
 
}
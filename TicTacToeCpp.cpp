// TicTacToeCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define ll long long
#include <iostream>

//#include <utility>
#include <vector>
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

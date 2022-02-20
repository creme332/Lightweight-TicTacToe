#include <iostream>
#include <stdlib.h> //used to clear terminal screen each round
using namespace std;

const char emptyspot = '.'; const char x = 'X'; const char o = 'O';
const char ongoing = 'n'; //game state = ongoing if no winner yet and board not full

char board[3][3] = { 
    {emptyspot,emptyspot,emptyspot},
    {emptyspot,emptyspot,emptyspot},
    {emptyspot,emptyspot,emptyspot}
};
void OutputBoard() {
    system("CLS"); //clear previous board from terminal
    cout << "Use format <row><space><column> where row, column are 1-3" << endl;
    cout <<"_____________"<< endl;
    for (int row = 0;row < 3;row++) {
        for (int col = 0;col < 3;col++) {
            if(col==2){
                cout << "| " <<board[row][col] << " |";
            }else{
                cout << "| " <<board[row][col] << " ";
            }
        }
        cout<<endl;
        if(row==2){
        cout <<"|___|___|___|"<< endl;

        }else{
        cout <<"|---|---|---|"<< endl;
        }
    }
};
char UpdateGameState() {
    // returns "X" if x won and "O" if o won 
    // returns "n" if game is ongoing - game has empty spots
    // returns "d" if draw 
    char k[2] = {x,o};
    bool HasEmptySpot = 0;

    for (int i = 0;i < 2;i++) {//for each player
        int count[4] = { 0,0,0,0 }; //count along each direction
        for (int r = 0;r < 3;r++) {
            for (int c = 0;c < 3;c++) {
                if (board[r][c] == k[i]) {count[0]++;} //count horizontally
                if (board[c][r] == k[i]) {count[1]++; } //count vertically
                if (r == c && board[r][c] == k[i]) { count[2]++;} //count along - diagonal
                if (r + c == 2 && board[r][c] == k[i]) {count[3]++;}  //count along + diagonal
                if (board[r][c] == emptyspot)HasEmptySpot=1;
            }
            for(int m=0;m<4;m++){if(count[m] == 3)return k[i];}//return winner if any
            count[0] = 0;count[1] = 0; //reset only for orthogonal directions
        }
    }
    if (HasEmptySpot)return ongoing;
    return 'd'; // draw
}
void UpdateBoard(bool turn, int row, int col) {
    //coordinates have already been validated
    // row n has index n-1 and column k has index k-1
    board[row-1][col-1] = (turn == 0)? o : x;
}
bool IsValid(int row, int col) {
    if (row > 0 && row < 4 && col>0 && col < 4 && board[row-1][col-1]==emptyspot)return 1;
    return 0;
}
int main()
{
    bool turnX = 0;// 0 - player o  1 - player x
    char state = ongoing;
    int row, col;

    while (state == ongoing) {
        OutputBoard();
        cout<< ((turnX==0)? "O's turn" : "X's turn") << endl;
        cin >> row >> col;

        while(IsValid(row, col) == 0){
            cout<<"Invalid coordinates. Enter again."<<endl;
            cin >> row >> col;
        }

        UpdateBoard(turnX, row, col);
        state = UpdateGameState();
        turnX = !(turnX); //swap turns 
    }
    OutputBoard();
    cout<<((state==o)? "Player O has won!":((state == x)? "Player X has won!" : "Draw"))<<endl;
}

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
    // returns "x" if x won and "o" if o won 
    // returns "n" if game is ongoing
    // returns "d" if draw 

    int xcount=0, ocount=0; //counts number of x and o

    //horizontal check
    for (int row = 0;row < 3;row++) {
        for (int col = 0;col < 3;col++) {
            if (board[row][col] == x) {xcount++;}
            if (board[row][col] == o) {ocount++;}
        }
        if (xcount == 3) {return x;}
        if (ocount == 3) {return o;}
        xcount = 0; ocount = 0;
    }

    //vertical check
    xcount = 0; ocount = 0;
    for (int col = 0;col < 3;col++) {
        for (int row = 0;row < 3;row++) {
            if (board[row][col] == x) {xcount++;}
            if (board[row][col] == o) {ocount++;}
        }
        if (xcount == 3) {return x;}
        if (ocount == 3) {return o;}
        xcount = 0; ocount = 0;
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

    //check if board has an emptyspot => can keep playing
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j] == emptyspot)return ongoing;
        }
    }
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

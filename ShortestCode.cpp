#include <iostream> 
const char x = 'X'; const char o = 'O'; const char null = '.';
std::string board = "...\n...\n...\n";
void OutputBoard() {
    for (auto ch : board) {std::cout<<ch;}
    std::cout << "\n";
};
int GameState() {
    // 1 : x won. -1 : o won.  0 : draw.  2 : keep playing.
    char player[2] = {x,o};
    bool HasEmptySpot = 0;

    for (int i = 0;i < 2;i++) {//for each player
        int count[4] = {0,0,0,0}; //for each direction
        for (int r = 0;r < 3;r++) {
            for (int c = 0;c < 3;c++) {
                if (board[r * 4 + c] == player[i]) { count[0]++; } //count horizontally
                if (board[c * 4 + r] == player[i]) { count[1]++; } //count vertically
                if (r == c && board[r * 4 + c]== player[i]) { count[2]++; } //count along - diagonal
                if (r + c == 2 && board[r * 4 + c] == player[i]) { count[3]++; }  //count along + diagonal
                if (board[r * 4 + c] == null)HasEmptySpot = 1;
            }
            for (int m = 0;m < 4;m++) {
                if (count[m] == 3) { return (i == 0) ? 1 : -1;}
            }
            count[0] = 0;count[1] = 0; //reset only for orthogonal directions
        }
    }
    return (HasEmptySpot) ? 2 : 0;
}
int minimax(int depth, bool maximizingplayer, int alpha, int beta) {
    int k = GameState();
    if (abs(k) == 1 || k == 0 )return 100*k; //Return 100 if X won, -100 if O won, and 0 if draw.

    int MaxEval = -1000, MinEval = 1000; //scores for maximising and minimising players
    for (int i = 0;i < board.length();i++) {
         if (board[i] == null) {
               board[i]= maximizingplayer? x:o;
               if (maximizingplayer) {
                   MaxEval = std::max(MaxEval, minimax(depth+1,0,alpha,beta) - depth);
                   board[i] = null;
                   alpha = std::max(alpha, MaxEval);
               }
               else {
                   MinEval = std::min(MinEval, minimax(depth+1, 1,alpha,beta) + depth);
                   board[i] = null;
                   beta = std::min(beta, MinEval);
               }
               if (beta <= alpha)break;
         }
    }
    return maximizingplayer==1 ? MaxEval : MinEval;
}
void AImove() {
    int bestmove=-1, MaxEval = INT_MIN;

    for (int i = 0;i < board.length();i++) {
        if (board[i] == null) {
            board[i] = x;
            int eval = minimax(0, 0,-9999,9999);
            if (eval > MaxEval){
                bestmove = i;
                MaxEval = eval;
            }
            board[i] = null;
        }
    }
    board[bestmove] = x;
}
int main(){
    bool AIturn=0; int state = 2,r, c;
    std::cout << "AI starts first? 1/0 ";
    std::cin >> AIturn;
    while (state == 2) {
         if (AIturn) {AImove();}
         else {
            std::cin >> r>>c;
            if(board[4*(r-1)+c-1] ==null)board[4 * (r - 1) + c - 1] = o;
        }
        state = GameState();
        AIturn = !(AIturn); 
        OutputBoard();
    }
    std::cout << ((state == 1) ? "AI won!" : "Draw") << "\n";
}

#include <iostream>
#include <vector>
#include <cassert>

using namespace std; 

const int OPEN = 0;
const int HUMAN = 1;
const int COMPUTER = 2;

vector<int> create_board() 
{
    vector<int> board;
    for (int i = 0; i < 9; i++){
        board.push_back(0);
    }
    
    return board;
}

void display_board(vector<int> input_board) 
{
    string divider = " | ";
    string line_divider = "\n ---+---+---\n  ";
    vector<string> board;
    
    for (int i = 0; i < input_board.size(); i++) {
        if (input_board[i] == 0) {
            board.push_back(" ");
        }
        else if (input_board[i] == 1) {
            board.push_back("X");
        }
        if (input_board[i] == 2) {
            board.push_back("O");
        }
    }

    cout << "  " << board[0] << divider << board[1] << divider << board[2] << line_divider << board[3] << divider << board[4] << divider << board[5] << line_divider << board[6] << divider << board[7] << divider << board[8] << "\n";
}

int ask_for_move(vector<int> board) 
{
    int move = 0;
    
    do {
        cout << "Make your move (Enter a number 1-9, numbers increment across row): ";
        cin >> move;
    } while (move < 1 || move > 9 || board[move-1] != OPEN);
    
    return move;
}

int check_win(vector<int> board) 
{
    int won = 0; 
    
    // CHECK TIE (end game)
    won = 3;                                    // 3 is tied value (0 is keep playing, 1 is human winner, 2 is computer winner)                          
    for (int i = 0; i < board.size(); i++) {
        //cout << board.size();
        if (board[i] == OPEN) {
            //cout << board[i];
            won = 0;
        }
    }
    
    // CHECK WINNER
    if (board[0] != OPEN && board[0] == board[1] && board[1] == board[2]) {
        won = board[0];
    } else if (board[3] != OPEN && board[3] == board[4] && board[4] == board[5]) {
        won = board[3];
    } else if (board[6] != OPEN && board[6] == board[7] && board[7] == board[8]) {
        won = board[6];
    } else if (board[0] != OPEN && board[0] == board[3] && board[3] == board[6]) {
        won = board[0];
    } else if (board[1] != OPEN && board[1] == board[4] && board[4] == board[7]) {
        won = board[1];
    } else if (board[2] != OPEN && board[2] == board[5] && board[5] == board[8]) {
        won = board[2];
    } else if (board[0] != OPEN && board[0] == board[4] && board[4] == board[8]) {
        won = board[0];
    } else if (board[2] != OPEN && board[2] == board[4] && board[4] == board[6]) {
        won = board[2];
    } 
    
    return won;
}

int ai_move(vector<int> board, bool isComputerTurn) 
{
    if (check_win(board) == 1) {
        return -10;
    }
    
    if (check_win(board) == 2) {
        return 10;
    }
    
    if (check_win(board) == 3) {
        return 0;
    }
    
    if (isComputerTurn) {
        int maximum = -1000;
        
        for (int i = 0; i < board.size(); i++) {
            if (board[i] == OPEN) {
                board[i] = COMPUTER;
                maximum = max(maximum, ai_move(board, !isComputerTurn));
                board[i] = OPEN;
            }
        }
        return maximum;
    } 
    
    else {
        int minimum = 1000;
        
        for (int i = 0; i < board.size(); i++) {
            if (board[i] == OPEN) {
                board[i] = HUMAN;
                minimum = min(minimum, ai_move(board, !isComputerTurn));
                board[i] = OPEN;
            }
        }
        return minimum;
    }
} 

int best_move(vector<int> board) 
{
    int best = -1000;
    int move_coordinate = -1;
    int possible_better;
    for (int i = 0; i < board.size(); i++) {
        
        if (board[i] == OPEN) {
            board[i] = COMPUTER;
            possible_better = ai_move(board, false);
            board[i] = OPEN;
        }
        if (possible_better > 10) {
            possible_better = -20;
        }
        if (best < possible_better) {
            best = possible_better;
            move_coordinate = i;
        }
    }
    return move_coordinate+1;
}

int main() 
{
    int player = 0;
    
    vector<int> current_board = create_board();
    display_board(current_board);
    
    while (check_win(current_board) == 0) {
        
        if (player % 2 == 0) {
            int move = ask_for_move(current_board);
            current_board[move-1] = HUMAN;    
        }
        else if (player % 2 == 1) {
            cout << "\n";
            int move_coord = best_move(current_board);
            current_board[move_coord-1] = COMPUTER;    
        }        
        
        display_board(current_board);
        player ++;
    }
    
    if (check_win(current_board) == 1) {
        cout << "game over... Daanya you messed up the code\n";
    } else if (check_win(current_board) == 2) {
        cout << "GAME OVER - COMPUTER WINS!\n";
    } else if (check_win(current_board) == 3) {
        cout << "GAME OVER - TIE\n";
    }
    
    return 0;
}

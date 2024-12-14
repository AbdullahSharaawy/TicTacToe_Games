#pragma once
#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <cctype>  
using namespace std;

class TicTacToeBoard : public Board<char> {
    char winer_Symbol;
public:
    
    TicTacToeBoard();
    void clear_Board();
    bool update_board(int x, int y, char symbol);
    void display_board();
    bool is_win();
    char get_winer_Symbol();
    bool is_draw();
    bool game_is_over();
    char get_cell(int x, int y);

};

class TicTacToePlayer : public Player<char> {
public:
    TicTacToePlayer(string name, char symbol);
    void getmove(int& x, int& y);

};


class TicTacToeRandom_Player : public RandomPlayer<char> {
public:
    TicTacToeRandom_Player(char symbol);
    void getmove(int& x, int& y);
};

//======================================================

TicTacToeBoard::TicTacToeBoard() {
    this->rows = this->columns = 3;
    this->board = new char* [this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

void TicTacToeBoard::clear_Board(){
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    n_moves = 0;
}





bool TicTacToeBoard::update_board(int a, int b, char mark) {

    if (!(a < 0 || a >= this->rows || b < 0 || b >= this->columns) && (this->board[a][b] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[a][b] = 0;
        }
        else {
            this->n_moves++;
            this->board[a][b] = toupper(mark);
        }

        return true;
    }
    return false;
}

void TicTacToeBoard::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

bool TicTacToeBoard::is_win() {
    
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            if (board[i][0] || board[0][i] == 'X') {
                winer_Symbol = 'X';
                return true;
            }
            else {
                winer_Symbol = 'O';
                return true;
            }
            
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        if (board[0][0] || board[0][2] == 'X') {
            winer_Symbol = 'X';
            return true;
        }
        else {
            winer_Symbol = 'O';
            return true;
        }
    }

    return false;
}

char TicTacToeBoard::get_winer_Symbol() {
    return winer_Symbol;
}

bool TicTacToeBoard::is_draw() {
    return (this->n_moves == 9 && !is_win());
}


bool TicTacToeBoard::game_is_over() {
    return is_win() || is_draw();
}

char TicTacToeBoard::get_cell(int x, int y) {
    return board[x][y];
}

TicTacToePlayer::TicTacToePlayer(string name, char symbol) : Player<char>(name, symbol) {}

void TicTacToePlayer::getmove(int& a, int& b) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    while (true) {
        cin >> a >> b;

        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
        }
        else {
            break; // Exit the loop if input is valid
        }
    }
    
}

TicTacToeRandom_Player::TicTacToeRandom_Player(char symbol) : RandomPlayer<char>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  
}

void TicTacToeRandom_Player::getmove(int& a, int& b ) {
    a = rand() % this->dimension;  
    b = rand() % this->dimension;
}




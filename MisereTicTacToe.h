#ifndef _MisereTicTacToe_H
#define _MisereTicTacToe_H
#include <utility>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <cctype>
#include "BoardGame_Classes.h"

using namespace std;


extern string player1_name;
extern string player2_name;

template <typename T>
class MisereTicTacToe_Board : public Board<T> {
public:
    MisereTicTacToe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    int x_count();
    int o_count();
    void swap_player_names();
    bool game_is_over() override;
    void set_players(Player<T>* player1, Player<T>* player2) {
        this->players[0] = player1;
        this->players[1] = player2;
    }
    
private:
    T board[3][3];
    int n_moves;
    Player<T>* players[2];
    int current_player;
    bool GameOver = false;
};

template <typename T>
class MisereTicTacToe_Player : public Player<T> {
public:
    MisereTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int& x, int& y) override;
    MisereTicTacToe_Player<T>& operator=(const MisereTicTacToe_Player<T>& other);
};

template <typename T>
MisereTicTacToe_Player<T>& MisereTicTacToe_Player<T>::operator=(const MisereTicTacToe_Player<T>& other) {
    if (this != &other) {
        this->name = other.name;
        this->symbol = other.symbol;
    }
    return *this;
}

template <typename T>
class MisereTicTacToe_Random_Player : public RandomPlayer<T> {
public:
    MisereTicTacToe_Random_Player(T symbol) : RandomPlayer<T>( symbol) { srand(static_cast<unsigned int>(time(0))); }
    void getmove(int& x, int& y) override;

};

template <typename T>
MisereTicTacToe_Board<T>::MisereTicTacToe_Board() {
    this->n_moves = 0;
    this->current_player = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            this->board[i][j] = 0;
        }
    }
    this->players[0] = nullptr;
    this->players[1] = nullptr;
}

template <typename T>
bool MisereTicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    if (GameOver)
        return true;
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void MisereTicTacToe_Board<T>::display_board() {
    if (!GameOver)
    {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << " " << (this->board[i][j] == 0 ? " " : string(1, this->board[i][j])) << " ";
                if (j < 2) cout << "|";
            }
            cout << endl;
            if (i < 2) cout << "---+---+---\n";
        }
        cout << endl;
   }
    
}



template <typename T>
int MisereTicTacToe_Board<T>::x_count() {
    int count = 0;

    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] == this->board[i][1] &&
            this->board[i][1] == this->board[i][2] &&
            this->board[i][0] == 'X') {
            count++;
            return count; 
        }

        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] == this->board[1][i] &&
                this->board[1][i] == this->board[2][i] &&
                this->board[0][i] == 'X') {
                count++;
                return count;  
            }
        }
    }
    if (this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2] &&
        this->board[0][0] == 'X') {
        count++;
        return count;  
    }

    if (this->board[0][2] == this->board[1][1] &&
        this->board[1][1] == this->board[2][0] &&
        this->board[0][2] == 'X') {
        count++;
        return count;  
    }

    return count;
}

template <typename T>
int MisereTicTacToe_Board<T>::o_count() {
    int count = 0;

    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] == this->board[i][1] &&
            this->board[i][1] == this->board[i][2] &&
            this->board[i][0] == 'O') {
            count++;
            return count; 
        }

        for (int i = 0; i < 3; i++) {
            if (this->board[0][i] == this->board[1][i] &&
                this->board[1][i] == this->board[2][i] &&
                this->board[0][i] == 'O') {
                count++;
                return count;  
            }
        }
    }
    if (this->board[0][0] == this->board[1][1] &&
        this->board[1][1] == this->board[2][2] &&
        this->board[0][0] == 'O') {
        count++;
        return count;  
    }

    if (this->board[0][2] == this->board[1][1] &&
        this->board[1][1] == this->board[2][0] &&
        this->board[0][2] == 'O') {
        count++;
        return count; 
    }

    return count;
}

template <typename T>
void MisereTicTacToe_Board<T>::swap_player_names() {
    string temp = player1_name;
    player1_name = player2_name;
    player2_name = temp;
}

template <typename T>
bool MisereTicTacToe_Board<T>::is_win() {
    if (!GameOver)
    {
        int x = x_count();
        int o = o_count();

        if (x > o) {
            cout << player2_name << " wins!\n";
            GameOver = true;
            return false;// to prevent the game manager from print the player name
        }
        else if (o > x) {
            cout << player1_name << " wins!\n";
            GameOver = true;
            return false;
        }

   }
    
    return false;
}


template <typename T>
bool MisereTicTacToe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !GameOver);// i replaced is_win() with GameOver
}

template <typename T>
bool MisereTicTacToe_Board<T>::game_is_over() { // i replaced is_win() with GameOver
    return  is_draw() || GameOver;
}

template <typename T>
void MisereTicTacToe_Player<T>::getmove(int& x, int& y) {
    bool validMove = false;
    while (!validMove) {
        cout << this->getname() << ", enter your move (row and column): ";
        cin >> x >> y;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. row and column values between 0 and 4.\n";
        }
        else if (x >= 0 && x < 3 && y >= 0 && y < 3) {
            validMove = true;
        }
        else {
            cout << "Invalid input. row and column values between 0 and 4.\n";
        }
    }
}

template <typename T>
void MisereTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
}

#endif

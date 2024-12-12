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

extern Player<char>* name[2];

template <typename T>
class MisereTicTacToe_Board : public Board<T> {
public:
    MisereTicTacToe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void swap_players();
    void set_players(Player<T>* player1, Player<T>* player2) {
        this->players[0] = player1;
        this->players[1] = player2;
    }
private:
    T board[3][3];
    int n_moves;
    Player<T>* players[2];
    int current_player;
};

template <typename T>
class MisereTicTacToe_Player : public Player<T> {
public:
    MisereTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}
    void getmove(int& x, int& y) override;
};

template <typename T>
class MisereTicTacToe_Random_Player : public Player<T> {
public:
    MisereTicTacToe_Random_Player(T symbol) : Player<T>("Computer", symbol) { srand(static_cast<unsigned int>(time(0))); }
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
}

template <typename T>
bool MisereTicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < 3 && y >= 0 && y < 3 && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void MisereTicTacToe_Board<T>::display_board() {
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

template <typename T>
bool MisereTicTacToe_Board<T>::is_win() {

    for (int i = 0; i < 3; i++) {
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0)
            return true;
            
        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)
            return true;
    }
    
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0)
        return true;
        
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)
        return true;

    return false;
}

template <typename T>
bool MisereTicTacToe_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool MisereTicTacToe_Board<T>::game_is_over() {
    if (is_win()) {
        cout << "\n" << players[current_player]->getname() << " loses the game!\n";
        return true;
    }
    if (is_draw()) {
        cout << "\nThe game is a draw!\n";
        return true;
    }
    return false;
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

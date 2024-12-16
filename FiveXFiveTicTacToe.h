#ifndef _FiveXFiveTicTacToe_H
#define _FiveXFiveTicTacToe_H
#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "BoardGame_Classes.h"
#include <limits>
using namespace std;
extern string playerName_X;

int x, o;

template <typename T>
class FiveXFiveTicTacToe_Board : public Board<T> {
public:
    FiveXFiveTicTacToe_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

    void set_players(Player<T>* player1, Player<T>* player2) {
        this->players[0] = player1;
        this->players[1] = player2;
    }

    int x_count();
    int o_count();

private:
    bool player_x = false;
    T board[5][5];
    int n_moves;
    Player<T>* players[2];
    int current_player;
};

template <typename T>
class FiveXFiveTicTacToe_Player : public Player<T> {
public:
    FiveXFiveTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override;

   FiveXFiveTicTacToe_Player<T>& operator=(const FiveXFiveTicTacToe_Player<T>& other);
};

template <typename T>
FiveXFiveTicTacToe_Player<T>& FiveXFiveTicTacToe_Player<T>::operator=(const FiveXFiveTicTacToe_Player<T>& other) {
    if (this != &other) {  // Avoid self-assignment
        this->name = other.name;
        this->symbol = other.symbol;
    }
    return *this;
}
template <typename T>
class FiveXFiveTicTacToe_Random_Player : public RandomPlayer<T> {
public:
    FiveXFiveTicTacToe_Random_Player(T symbol) : RandomPlayer<T>( symbol) {
        srand(static_cast<unsigned int>(time(0)));
    }


    void getmove(int& x, int& y) override;

private:
    int dimension;
};

template <typename T>
FiveXFiveTicTacToe_Board<T>::FiveXFiveTicTacToe_Board() {
    this->n_moves = 0;
    this->current_player = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            this->board[i][j] = 0;
        }
    }
}

template <typename T>
bool FiveXFiveTicTacToe_Board<T>::update_board(int x, int y, T symbol) {
    if (x >= 0 && x < 5 && y >= 0 && y < 5 && this->board[x][y] == 0) {
        this->board[x][y] = toupper(symbol);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void FiveXFiveTicTacToe_Board<T>::display_board() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << " " << (this->board[i][j] == 0 ? " " : string(1, this->board[i][j])) << " ";
            if (j < 4) cout << "|";
        }
        cout << endl;
        if (i < 4) cout << "---+---+---+---+---\n";
    }
    cout << endl;
}


template <typename T>
int FiveXFiveTicTacToe_Board<T>::x_count() {
    int count = 0;
    if (this->n_moves != 24) {
        return count;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[i][j] == 'X' && this->board[i][j + 1] == 'X' && this->board[i][j + 2] == 'X') {
                count++;
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[j][i] == 'X' && this->board[j + 1][i] == 'X' && this->board[j + 2][i] == 'X') {
                count++;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (this->board[i][i] == 'X' && this->board[i + 1][i + 1] == 'X' && this->board[i + 2][i + 2] == 'X') {
            count++;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (this->board[1 + i][i] == 'X' && this->board[i + 2][i + 1] == 'X' && this->board[i + 3][i + 2] == 'X') {
            count++;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (this->board[i][i + 1] == 'X' && this->board[i + 1][i + 2] == 'X' && this->board[i + 2][i + 3] == 'X') {
            count++;
        }
    }
    if (this->board[0][4] == 'X' && this->board[1][3] == 'X' && this->board[2][2] == 'X')
        count++;
    if (this->board[1][3] == 'X' && this->board[2][2] == 'X' && this->board[3][1] == 'X')
        count++;
    if (this->board[2][2] == 'X' && this->board[3][1] == 'X' && this->board[4][0] == 'X')
        count++;
    if (this->board[2][0] == 'X' && this->board[3][1] == 'X' && this->board[4][2] == 'X')
        count++;
    if (this->board[0][2] == 'X' && this->board[1][3] == 'X' && this->board[2][4] == 'X')
        count++;
    if (this->board[1][4] == 'X' && this->board[2][3] == 'X' && this->board[3][2] == 'X')
        count++;
    if (this->board[2][3] == 'X' && this->board[3][2] == 'X' && this->board[4][1] == 'X')
        count++;
    if (this->board[2][4] == 'X' && this->board[3][3] == 'X' && this->board[4][2] == 'X')
        count++;
    if (this->board[0][3] == 'X' && this->board[1][2] == 'X' && this->board[2][1] == 'X')
        count++;
    if (this->board[1][2] == 'X' && this->board[2][1] == 'X' && this->board[3][0] == 'X')
        count++;
    if (this->board[0][2] == 'X' && this->board[1][1] == 'X' && this->board[2][0] == 'X')
        count++;
    return count;
}

template <typename T>
int FiveXFiveTicTacToe_Board<T>::o_count() {
    int count = 0;
    if (this->n_moves != 24) {
        return count;
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[i][j] == 'O' && this->board[i][j + 1] == 'O' && this->board[i][j + 2] == 'O') {
                count++;
            }
        }
    }
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            if (this->board[j][i] == 'O' && this->board[j + 1][i] == 'O' && this->board[j + 2][i] == 'O') {
                count++;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (this->board[i][i] == 'O' && this->board[i + 1][i + 1] == 'O' && this->board[i + 2][i + 2] == 'O') {
            count++;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (this->board[1 + i][i] == 'O' && this->board[i + 2][i + 1] == 'O' && this->board[i + 3][i + 2] == 'O') {
            count++;
        }
    }
    for (int i = 0; i < 2; i++) {
        if (this->board[i][i + 1] == 'O' && this->board[i + 1][i + 2] == 'O' && this->board[i + 2][i + 3] == 'O') {
            count++;
        }
    }
    if (this->board[0][4] == 'O' && this->board[1][3] == 'O' && this->board[2][2] == 'O')
        count++;
    if (this->board[1][3] == 'O' && this->board[2][2] == 'O' && this->board[3][1] == 'O')
        count++;
    if (this->board[2][2] == 'O' && this->board[3][1] == 'O' && this->board[4][0] == 'O')
        count++;
    if (this->board[2][0] == 'O' && this->board[3][1] == 'O' && this->board[4][2] == 'O')
        count++;
    if (this->board[0][2] == 'O' && this->board[1][3] == 'O' && this->board[2][4] == 'O')
        count++;
    if (this->board[1][4] == 'O' && this->board[2][3] == 'O' && this->board[3][2] == 'O')
        count++;
    if (this->board[2][3] == 'O' && this->board[3][2] == 'O' && this->board[4][1] == 'O')
        count++;
    if (this->board[2][4] == 'O' && this->board[3][3] == 'O' && this->board[4][2] == 'O')
        count++;
    if (this->board[0][3] == 'O' && this->board[1][2] == 'O' && this->board[2][1] == 'O')
        count++;
    if (this->board[1][2] == 'O' && this->board[2][1] == 'O' && this->board[3][0] == 'O')
        count++;
    if (this->board[0][2] == 'O' && this->board[1][1] == 'O' && this->board[2][0] == 'O')
        count++;
    return count;
}

template <typename T>
bool FiveXFiveTicTacToe_Board<T>::is_win() {
    x = x_count();
    o = o_count();
    // in this condition function will return false to ignore display name of player O as a winner , where i print name player x with out pointer of players that exist in game manager
    if (x > o) {

        if (player_x)
            return false;
       
        cout << "score player x= " << x << endl
            << "score player o= " << o << endl;
        cout << playerName_X<<" wins" << endl;
        player_x = true;
        return false;
    }
    else if (o > x) {
        cout << "score player x= " << x << endl
            << "score player o= " << o << endl;
        
        return true;
    }
    else {
        return false;
    }
}

template <typename T>
bool FiveXFiveTicTacToe_Board<T>::is_draw() {
if (player_x)
        return false;
else if (this->n_moves == 24 && !is_win()) {
        cout << "score player x= " << x << endl
            << "score player o= " << o << endl;
    }
    return (this->n_moves == 24 && !is_win());
}

template <typename T>
bool FiveXFiveTicTacToe_Board<T>::game_is_over() {
    return is_win() || is_draw() || player_x;
}

template <typename T>
void FiveXFiveTicTacToe_Player<T>::getmove(int& x, int& y) {
    bool validMove = false;
    while (!validMove) {
        cout << this->getname() << ", enter your move (row and column): ";
        cin >> x >> y;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. row and column values between 0 and 4.\n";
        }
        else if (x >= 0 && x < 5 && y >= 0 && y < 5) {
            validMove = true;
        }
        else {
            cout << "Invalid input. row and column values between 0 and 4.\n";
        }
    }
}

template <typename T>
void FiveXFiveTicTacToe_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 5;
    y = rand() % 5;
}

#endif

#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <set>
#include <cstdlib> 
#include <ctime> 
using namespace std;

class NumericalTicTacToeBoard : public Board<int> {
private:
    set<int> used_numbers;
public:
    NumericalTicTacToeBoard();
    ~NumericalTicTacToeBoard();
    bool update_board(int x, int y, int number) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};


class NumericalTicTacToePlayer : public Player<int> {
protected:
    set <int> available_numbers;
public:
    NumericalTicTacToePlayer(string n, int symbol, bool odd);
    void getmove(int& x, int& y) override;
};  


class RandomNumericalTicTacToePlayer : public NumericalTicTacToePlayer {
public:
    RandomNumericalTicTacToePlayer(string n, int symbol, bool odd);
    void getmove(int& x, int& y) override;
};

//==============================================================
// implementation

NumericalTicTacToeBoard::NumericalTicTacToeBoard() {
    rows = columns = 3;
    board = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new int[columns];
        for (int j = 0; j < columns; j++) {
            board[i][j] = 0;
        }
    }
}

NumericalTicTacToeBoard::~NumericalTicTacToeBoard() {
    for (int i = 0; i < rows; ++i) delete[] board[i];
    delete[] board;
}

bool NumericalTicTacToeBoard::update_board(int x, int y, int number) {
    if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0 || used_numbers.count(number)) {
        cout << "invaled position. try again";
        return false;
    }
    board[x][y] = number;
    used_numbers.insert(number);
    n_moves++;
    return true;
}

void NumericalTicTacToeBoard::display_board() {
    cout << "\nBoard:\n";
    cout << "\t\t0\t\t1\t\t2\n\n";
    for (int i = 0; i < rows; ++i) {
        cout << "\t" << i;
        for (int j = 0; j < columns; ++j) {
            cout << "\t" << "(x, y) " << (board[i][j] == 0 ? "." : to_string(board[i][j])) << "  |" << " ";
        }
        cout << "\n\n";
    }
}

bool NumericalTicTacToeBoard::is_win() {
    for (int i = 0; i < rows; ++i) {
        if ((board[i][0] + board[i][1] + board[i][2] >= 15) &&
            (((board[i][0] % 2 != 0) && (board[i][1] % 2 != 0) && (board[i][2] % 2 != 0))
                || ((board[i][0] % 2 == 0) && (board[i][1] % 2 == 0) && (board[i][2] % 2 == 0))))
            return true;
    }
    for (int j = 0; j < columns; ++j) {
        if ((board[0][j] + board[1][j] + board[2][j] >= 15) &&
            (((board[0][j] % 2 != 0) && (board[1][j] % 2 != 0) && (board[2][j] % 2 != 0))
                || ((board[1][j] % 2 == 0) && (board[1][j] % 2 == 0) && (board[2][j] % 2 == 0))))
            return true;
    }
    if ((board[0][0] + board[1][1] + board[2][2] >= 15) &&
        (((board[0][0] % 2 != 0) && (board[1][1] % 2 != 0) && (board[2][2] % 2 != 0))
            || ((board[0][0] % 2 == 0) && (board[1][1] % 2 == 0) && (board[2][2] % 2 == 0)))
        || (board[0][2] + board[1][1] + board[2][0] >= 15) &&
        (((board[0][2] % 2 != 0) && (board[1][1] % 2 != 0) && (board[2][0] % 2 != 0))
            || ((board[0][2] % 2 == 0) && (board[1][1] % 2 == 0) && (board[2][0] % 2 == 0)))) {
        return true;
    }
    return false;
}

bool NumericalTicTacToeBoard::is_draw() {
    return n_moves == 9 && !is_win();
}

bool NumericalTicTacToeBoard:: game_is_over() {
    return is_win() || is_draw();
}

NumericalTicTacToePlayer::NumericalTicTacToePlayer(string n, int symbol, bool odd) : Player<int>(n, symbol) {
    for (int i = (odd ? 1 : 2); i <= 9; i += 2) {
        available_numbers.insert(i);
    }
}

void NumericalTicTacToePlayer::getmove(int& x, int& y) {

    int number;
    cout << this->name;
    cout << "'s available numbers:( " << *available_numbers.begin();
    for (int i : available_numbers) {
        if (i == *available_numbers.begin()) { continue; }
        cout << " ," << i;
    }
    cout << " )\n";
    cout << "enter your move(number x y): ";
    cin >> number >> x >> y;
    if (available_numbers.count(number)) {
        available_numbers.erase(number);
        symbol = number;
    }
    else {
        cout << "Invalid number. Try again.\n";
        getmove(x, y);
    }
}

RandomNumericalTicTacToePlayer::RandomNumericalTicTacToePlayer(string n, int symbol, bool odd)
    : NumericalTicTacToePlayer(n, symbol, odd) {
    srand(static_cast<unsigned int>(time(0)));
}

void RandomNumericalTicTacToePlayer::getmove(int& x, int& y)  {
    int number;
    vector<int> available_numbers_vec(available_numbers.begin(), available_numbers.end());

    int random_index = rand() % available_numbers_vec.size();
    number = available_numbers_vec[random_index];
    available_numbers.erase(number);
    symbol = number;

    x = rand() % 3;
    y = rand() % 3;

}

#endif


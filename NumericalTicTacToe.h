#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <set>
#include <cstdlib> 
#include <ctime> 
using namespace std;

// Define the NumericalTicTacToe Board
class NumericalTicTacToeBoard : public Board<int> {
private:
    set<int> used_numbers;
public:
    NumericalTicTacToeBoard() {
        rows = columns = 3;
        board = new int* [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new int[columns] {0}; 
        }
    }

    ~NumericalTicTacToeBoard() {
        for (int i = 0; i < rows; ++i) delete[] board[i];
        delete[] board;
    }

    bool update_board(int x, int y, int number) override {
        if (x < 0 || x >= rows || y < 0 || y >= columns || board[x][y] != 0 || used_numbers.count(number)) {
            return false;
        }
        board[x][y] = number;
        used_numbers.insert(number);
        n_moves++;
        return true;
    }

    void display_board() override {
        cout << "\nBoard:\n";
        cout << "\t\t0\t\t1\t\t2\n\n";
        for (int i = 0; i < rows; ++i) {
            cout << "\t" << i;
            for (int j = 0; j < columns; ++j) {
                cout<< "\t" << "(x, y) " << (board[i][j] == 0 ? "." : to_string(board[i][j])) << "  |" << " ";
            }
            cout << "\n\n";
        }
    }

    bool is_win() override {
        for (int i = 0; i < rows; ++i) {
            if ((board[i][0] + board[i][1] + board[i][2] >= 15) && 
               (((board[i][0] % 2 != 0) && (board[i][1] % 2 != 0) && (board[i][2] % 2 != 0))
               ||((board[i][0] % 2 == 0) && (board[i][1] % 2 == 0) && (board[i][2] % 2 == 0)))) 
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

    bool is_draw() override {
        return n_moves == 9 && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

// Define a Player for Numerical Tic-Tac-Toe
class NumericalTicTacToePlayer : public Player<int> {
protected:
    set<int> available_numbers;
public:
    NumericalTicTacToePlayer(string n, int symbol, bool odd) : Player<int>(n, symbol) {
        for (int i = (odd ? 1 : 2); i <= 9; i += 2) {
            available_numbers.insert(i);
        }
    }

    void getmove(int& x, int& y) override {
        int number;
        cout << this->name << " (" << this->symbol << "), enter your move (number x y): ";
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
};  

class RandomNumericalTicTacToePlayer : public NumericalTicTacToePlayer {
public:
    RandomNumericalTicTacToePlayer(string n, int symbol, bool odd)
        : NumericalTicTacToePlayer(n, symbol, odd) {
        srand(static_cast<unsigned int>(time(0)));
    }

    void getmove(int& x, int& y) override {
        cout << "computer is playing";
        int number;
        vector<int> available_numbers_vec(available_numbers.begin(), available_numbers.end());

        // Randomly select a number
        int random_index = rand() % available_numbers_vec.size();
        number = available_numbers_vec[random_index];
        available_numbers.erase(number);
        symbol = number;

        // Randomly select an empty cell
            x = rand() % 3; 
            y = rand() % 3;
         
    }
};

#endif


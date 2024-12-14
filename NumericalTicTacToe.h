#ifndef NUMERICAL_TICTACTOE_H
#define NUMERICAL_TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <set>
#include <cstdlib> 
#include <ctime> 
using namespace std;
template <typename T>
class NumericalTicTacToeBoard : public Board<T> {
private:
    set<int> used_numbers;
public:
    NumericalTicTacToeBoard();
    ~NumericalTicTacToeBoard();
    bool update_board(int x, int y, int number);
    void display_board();
    bool is_win();
    bool is_draw();
    bool Is_empty(int x, int y);
    bool game_is_over();
};

template <typename T>
class NumericalTicTacToePlayer : public Player<T> {
protected:
    set <int> available_numbers;
public:
    NumericalTicTacToePlayer(string n, int symbol, bool odd);
    void getmove(int& x, int& y) ;
};  

template <typename T>
class RandomNumericalTicTacToePlayer : public  RandomPlayer<T>{
protected:
    set <int> available_numbers;
public:
    RandomNumericalTicTacToePlayer(int symbol, bool odd);
    void getmove(int& x, int& y) ;
};

//==============================================================
// implementation
template <typename T>
NumericalTicTacToeBoard<T>::NumericalTicTacToeBoard() {
    this->rows = this->columns = 3;
    this->board = new int* [this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
}
template <typename T>
NumericalTicTacToeBoard<T>::~NumericalTicTacToeBoard() {
    for (int i = 0; i < this->rows; ++i) delete[] this->board[i];
    delete[] this->board;
}
template <typename T>
bool NumericalTicTacToeBoard<T>::update_board(int x, int y, int number) {
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0 || this->used_numbers.count(number)) {
        return false;
    }
    this->board[x][y] = number;
    this->used_numbers.insert(number);
    this->n_moves++;
    return true;
}
template <typename T>
void NumericalTicTacToeBoard<T>::display_board() {
    cout << "\nBoard:\n";
    cout << "\t\t0\t\t1\t\t2\n\n";
    for (int i = 0; i < this->rows; ++i) {
        cout << "\t" << i;
        for (int j = 0; j < this->columns; ++j) {
            cout << "\t" << "(x, y) " << (this->board[i][j] == 0 ? "." : to_string(this->board[i][j])) << "  |" << " ";
        }
        cout << "\n\n";
    }
}
template <typename T>
bool NumericalTicTacToeBoard<T>::is_win() {
    for (int i = 0; i < this->rows; ++i) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] >= 15) &&
            (((this->board[i][0] % 2 != 0) && (this->board[i][1] % 2 != 0) && (this->board[i][2] % 2 != 0))
                || ((this->board[i][0] % 2 == 0) && (this->board[i][1] % 2 == 0) && (this->board[i][2] % 2 == 0))))
            return true;
    }
    for (int j = 0; j < this->columns; ++j) {
        if ((this->board[0][j] + this->board[1][j] + this->board[2][j] >= 15) &&
            (((this->board[0][j] % 2 != 0) && (this->board[1][j] % 2 != 0) && (this->board[2][j] % 2 != 0))
                || ((this->board[1][j] % 2 == 0) && (this->board[1][j] % 2 == 0) && (this->board[2][j] % 2 == 0))))
            return true;
    }
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] >= 15) &&
        (((this->board[0][0] % 2 != 0) && (this->board[1][1] % 2 != 0) && (this->board[2][2] % 2 != 0))
            || ((this->board[0][0] % 2 == 0) && (this->board[1][1] % 2 == 0) && (this->board[2][2] % 2 == 0)))
        || (this->board[0][2] + this->board[1][1] + this->board[2][0] >= 15) &&
        (((this->board[0][2] % 2 != 0) && (this->board[1][1] % 2 != 0) && (this->board[2][0] % 2 != 0))
            || ((this->board[0][2] % 2 == 0) && (this->board[1][1] % 2 == 0) && (this->board[2][0] % 2 == 0)))) {
        return true;
    }
    return false;
}
template <typename T>
bool NumericalTicTacToeBoard<T>::is_draw() {
    return this->n_moves == 9 && !is_win();
}
template<typename T>
 bool NumericalTicTacToeBoard<T>::Is_empty(int x, int y)
{
    if (this->board[x][y] == 0)
        return true;
    return false;
}
template <typename T>
bool NumericalTicTacToeBoard<T>:: game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
NumericalTicTacToePlayer<T>::NumericalTicTacToePlayer(string n, int symbol, bool odd) : Player<int>(n, symbol) {
    for (int i = (odd ? 1 : 2); i <= 9; i += 2) {
        this->available_numbers.insert(i);
    }
}
template <typename T>
void NumericalTicTacToePlayer<T>::getmove(int& x, int& y) {

    int number;
    cout <<"player " << this->name << " your available nambers are ";
    cout << "( ";
    for (int i : this->available_numbers) {
        cout << i << " ";
    }
    cout << ")\n";
    cout << "enter your move(number x y): ";
   
    while (true) {
        cin >>number>> x >> y;

        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
            cout << ")\n";
            cout << "enter your move(number x y): ";
        }
        else {
            break; // Exit the loop if input is valid
        }
    }
    
    if (this->available_numbers.count(number)) {
        this->available_numbers.erase(number);
        this->symbol = number;
    }
    else {
        cout << "Invalid number. Try again.\n";
        getmove(x, y);
    }
}
template <typename T>
RandomNumericalTicTacToePlayer<T>::RandomNumericalTicTacToePlayer(int symbol, bool odd)
    : RandomPlayer<int>(symbol) {
    for (int i = (odd ? 1 : 2); i <= 9; i += 2) {
        this->available_numbers.insert(i);
    }
    srand(static_cast<unsigned int>(time(0)));
}
template <typename T>
void RandomNumericalTicTacToePlayer<T>::getmove(int& x, int& y)  {
    int number;
    vector<int> available_numbers_vec(this->available_numbers.begin(), this->available_numbers.end());
    
    x = rand() % 3;
    y = rand() % 3;
    
    int random_index = rand() % available_numbers_vec.size();
    number = available_numbers_vec[random_index];
    this->symbol = number;


}

#endif



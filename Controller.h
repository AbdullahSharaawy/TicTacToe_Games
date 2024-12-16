
#include <iostream>
#include "BoardGame_Classes.h"
#include "four_in_a_row.h"
#include"PyramicTicTacToeX_O.h"
#include"WORD_TICTACTOE.h"
#include"FourXFourTicTacToe.h"
#include"MisereTicTacToe.h"
#include "NumericalTicTacToe.h"
#include"TicTacToe_of_Ultimate.h"
#include <string>
#include"TicTacToe_5x5.h"
#include<iomanip>
#include <variant>
#include <memory>
#include <optional>
#include <fstream>
#include <vector>
using namespace std;
string playerName_X;
string player1_name;
string player2_name;
template <typename T>
class Controller
{
private:

   static Board<T>* createBoard(int SelectedBoard);

    static Player<T>* createHumanPlayer(int GameNumber, string PlayerName, char PlayerSymbol);
    static  RandomPlayer<T>* createComputerPlayer(int GameNumber, char PlayerSymbol);


    static void PrintMainMenu();
    static string selectGameName(int GameNumber);

    static  auto selectNameAndType(string GameName, char PlayerSymbol, Player<char>*& player, int GameNumber);
    static vector<string> getTicTacToeWords(string FileName);
    static string ReadFileName(string message);
public:
    static vector<string>TicTacToeWords;
    static void Start();
    static bool selectMove_X(char board[6][7], int& Row, int Column, char symbol);
    static void startNumerical();
    
};
template<typename T>
vector<string> Controller<T>::TicTacToeWords;

template <typename T>
void Controller<T>::startNumerical()
{
    int choice;
    Player<int>* players[2];
    NumericalTicTacToeBoard<int>* B = new NumericalTicTacToeBoard<int>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[0] = new NumericalTicTacToePlayer<int>(playerXName, 0, true);
        break;
    case 2:
        players[0] = new RandomNumericalTicTacToePlayer<int>(0, true);
        break;
    default:
        cout << "Invalid choice for Player 1. Exiting the game.\n";
        break;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
    case 1:
        players[1] = new NumericalTicTacToePlayer<int>(playerXName, 0, false);
        break;
    case 2:
        players[1] = new RandomNumericalTicTacToePlayer<int>(0, false);
        break;
    default:
        cout << "Invalid choice for Player 2. Exiting the game.\n";
        break;
    }

    // Create the game manager and run the game
    GameManager<int> game(B, players);
    game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

}
template<typename T>
void Controller<T>::PrintMainMenu()
{

    cout << "\n1- Pyramic Tic-Tac-Toe\n\n";
    cout << "2- Four-in-a-row\n\n";
    cout << "3- 5 x 5 Tic Tac Toe\n\n";
    cout << "4- Word Tic-tac-toe\n\n";
    cout << "5- Numerical Tic-Tac-Toe\n\n";
    cout << "6- Misere Tic Tac Toe\n\n";
    cout << "7- 4 x 4 Tic-Tac-Toe\n\n";
    cout << "8- Ultimate Tic Tac Toe\n\n";
    cout << "9- Exist\n\n";
    cout << "select Game Number (1->8): ";
}
template<typename T>
Board<T>* Controller<T>::createBoard(int SelectedBoard)
{
    switch (SelectedBoard)
    {
    case 1:
        return new PyramicTicTacToe_Board<T>();
        
    case 2:
        return new four_in_a_row_Board<T>();
        break;
    case 4:
        return new WORD_TICTACTOE_Board<T>(Controller::TicTacToeWords);
    case 7:
        return new FourXFourTicTacToe_Board<T>();
    case 3:
        return new FiveXFiveTicTacToe_Board<T>();
    case 6:
        return new MisereTicTacToe_Board<T>();
    case 8:
        return new tictactoe_ultimateBoard<T>();
   
    default:
        return nullptr;
        
    }
}
template<typename T>
RandomPlayer<T>* Controller<T>::createComputerPlayer(int GameNumber, char PlayerSymbol)
{
    switch (GameNumber)
    {
    case 1:
        return new PyramicTicTacToe_Random_Player<T>(PlayerSymbol);
        
    case 2:
        return new four_in_a_row_Random_Player<T>(PlayerSymbol);
       
    case 4:
        return new WORD_TICTACTOE_Random_Player<T>(PlayerSymbol);
       
    case 3:
        return new FiveXFiveTicTacToe_Random_Player<T>(PlayerSymbol);
       
    case 7:
        return new FourXFourTicTacToe_Random_Player<T>(PlayerSymbol);
       
    case 6:
        return new MisereTicTacToe_Random_Player<T>(PlayerSymbol);
    case 8:
        return new tictactoe_ultimateRandom_Player<T>(PlayerSymbol);
    default:

        break;
    }

}
template<typename T>
Player<T>* Controller<T>::createHumanPlayer(int GameNumber, string PlayerName, char PlayerSymbol)
{
    switch (GameNumber)
    {
    case 1:
        return new PyramicTicTacToe_Player<T>(PlayerName, PlayerSymbol);
        break;
    case 2:
        return new four_in_a_row_Player<T>(PlayerName, PlayerSymbol);
    case 4:
        return new WORD_TICTACTOE_Player<T>(PlayerName, PlayerSymbol);
    case 3:
        return new FiveXFiveTicTacToe_Player<T>(PlayerName, PlayerSymbol);
    case 7 :
        return new FourXFourTicTacToe_Player<T>(PlayerName, PlayerSymbol);
    case 6:
        return new MisereTicTacToe_Player<T>(PlayerName, PlayerSymbol);
    case 8:
        return new tictactoe_ultimatePlayer<T>(PlayerName, PlayerSymbol);
    default:
        break;
    }
}
template<typename T>
auto Controller<T>::selectNameAndType(string GameName, char PlayerSymbol, Player<char>*& player, int GameNumber)
{

    string playerName;
    int choice;
    GameName = selectGameName(GameNumber);
    cout << "\nWelcome to FCAI " << GameName << ". :)\n\n";

    // Set up player 1
    cout << "Enter Player" << PlayerSymbol << " name: ";
    cin >> playerName;
 
    if (PlayerSymbol == 'X')
        player1_name = playerName;
    else
        player2_name = playerName;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        cout << "Choose Player type:\n";
        cout << "1. Human\n";
        cout << "2. Random Computer\n";
        cin >> choice;
        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
        }
        else {
            break; // Exit the loop if input is valid
        }
    }

    
    if (PlayerSymbol == 'X')
        playerName_X = playerName;
    if (choice == 1)
    {
        player = createHumanPlayer(GameNumber, playerName, PlayerSymbol);
    }
    else player = createComputerPlayer(GameNumber, PlayerSymbol);

}

template<typename T>
string Controller<T>::selectGameName(int GameNumber)
{
    string GameName;
    switch (GameNumber)
    {
    case 1:
        GameName = "Pyramic Tic-Tac-Toe";
        break;
    case 2:
        GameName = "four-in-a-row";
        break;
    case 4:
        GameName="Word Tic-Tac-Toe";
        break;
    case 7:
        GameName="FourXFour Tic-Tac-Toe";
        break;
    case 3:
        GameName="FiveXFive Tic-Tac-Toe";
        break;
    case 6:
        GameName = "Misere TicTacToe";
    case 8:
        GameName = "Ultimate TicTacToe";
        break;
    case 5:
        GameName = "Numerical TicTacToe";
        break;
    default:
        break;
    }
    return GameName;
}
template<typename T>
vector <string> Controller<T>::getTicTacToeWords(string FileName)
{
    fstream File;
    vector <string>Words;
    File.open(FileName);
    if (File.is_open())
    {
        string word;
        while (getline(File, word))
        {
            Words.push_back(word);
        }
        File.close();
    }
    else cout << "the file is not exist\n";
    return Words;
}
template<typename T>
string Controller<T>::ReadFileName(string message)
{ 
    string FileName;
    while (true) {
        cout << message << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, FileName);

        // Check if the file exists
        ifstream file(FileName);
        if (file) {
            file.close();
            break;  // Exit loop if file exists
        }
        else {
            cout << "File does not exist. Please try again." << endl;
        }
    }
    return FileName;
}
template<typename T>
void Controller<T>::Start()
{
    
    int GameNumber;
    Player<char>* players[2];
    PrintMainMenu();
    while (true) {
        cin >> GameNumber;
        // Check if input is valid
        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a valid integer.\n";
            cout << "select Game Number (1->8): ";

        }
        else {
            break; // Exit the loop if input is valid
        }
    }
    Board<char>* Board=nullptr;
    if (GameNumber == 4)
    {
        Controller::TicTacToeWords = getTicTacToeWords(ReadFileName("please enter file name of Words: "));
         Board = createBoard(GameNumber);
        for (size_t i = 0; i < 2; i++)
        {

            selectNameAndType(selectGameName(GameNumber), i == 0 ? '1' : '2', players[i], GameNumber);
        }
    }
    else if (GameNumber==5)
    {
        Controller::startNumerical();
        
    }
    else if (GameNumber == 9)
    {
        exit(0);
    }
    else
    {
         Board = createBoard(GameNumber);
        for (size_t i = 0; i < 2; i++)
        {

            selectNameAndType(selectGameName(GameNumber), i==0?'X':'O', players[i], GameNumber);
        }

    }

    if (GameNumber != 5 )
    {
        for (size_t i = 0; i < 2; i++)
        {
            players[i]->setBoard(Board);
        }
        // Create the game manager and run the game
        GameManager<char> _GameManager(Board, players);
        _GameManager.run();

        // Clean up
        delete Board;
        for (int i = 0; i < 2; ++i) {
            delete players[i];
        }

    }
    Controller::Start();
}

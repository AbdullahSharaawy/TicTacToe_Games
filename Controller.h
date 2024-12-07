
#include <iostream>
#include "BoardGame_Classes.h"
#include "four_in_a_row.h"
#include"TicTacToeX_O.h"
#include"WORD_TICTACTOE.h"
#include"FourXFourTicTacToe.h"
#include <string>
#include<iomanip>
#include <variant>
#include <memory>
#include <optional>
#include <fstream>
#include <vector>
using namespace std;
class Controller
{
private:

   static Board<char>* createBoard(int SelectedBoard);

    static Player<char>* createHumanPlayer(int GameNumber, string PlayerName, char PlayerSymbol);
    static  RandomPlayer<char>* createComputerPlayer(int GameNumber, char PlayerSymbol);


    static void PrintMainMenu();
    static string selectGameName(int GameNumber);

    static  auto selectNameAndType(string GameName, char PlayerSymbol, Player<char>*& player, int GameNumber);
    static vector<string> getTicTacToeWords(string FileName);
    static string ReadFileName(string message);
public:
    static vector<string>TicTacToeWords;
    static void Start();
    static bool selectMove_X(char board[6][7], int& Row, int Column, char symbol);

};
vector<string> Controller::TicTacToeWords;

void Controller::PrintMainMenu()
{

    cout << "\n1- Pyramic Tic-Tac-Toe\n\n";
    cout << "2- Four-in-a-row\n\n";
    cout << "3- 5 x 5 Tic Tac Toe\n\n";
    cout << "4- Word Tic-tac-toe\n\n";
    cout << "5- Numerical Tic-Tac-Toe\n\n";
    cout << "6- Misere Tic Tac Toe\n\n";
    cout << "7- 4 x 4 Tic-Tac-Toe\n\n";
    cout << "8- Ultimate Tic Tac Toe\n\n";
    cout << "select Game Number (1->8): ";
}
Board<char>* Controller::createBoard(int SelectedBoard)
{
    switch (SelectedBoard)
    {
    case 1:
        return new TicTacToe_Board<char>();
        
    case 2:
        return new four_in_a_row_Board<char>();
        break;
    case 4:
        return new WORD_TICTACTOE_Board<char>(Controller::TicTacToeWords);
    case 7:
        return new FourXFourTicTacToe_Board<char>();
    default:
        return nullptr;
        
    }
}
RandomPlayer<char>* Controller::createComputerPlayer(int GameNumber, char PlayerSymbol)
{
    switch (GameNumber)
    {
    case 1:
        return new TicTacToe_Random_Player<char>(PlayerSymbol);
        break;
    case 2:
        return new four_in_a_row_Random_Player<char>(PlayerSymbol);
        break;
    case 4:
        return new WORD_TICTACTOE_Random_Player<char>(PlayerSymbol);
        break;
        case 7:
        return new FourXFourTicTacToe_Random_Player<char>(PlayerSymbol);
        break;
    default:

        break;
    }

}
Player<char>* Controller::createHumanPlayer(int GameNumber, string PlayerName, char PlayerSymbol)
{
    switch (GameNumber)
    {
    case 1:
        return new TicTacToe_Player<char>(PlayerName, PlayerSymbol);
        break;
    case 2:
        return new four_in_a_row_Player<char>(PlayerName, PlayerSymbol);
    case 4:
        return new WORD_TICTACTOE_Player<char>(PlayerName, PlayerSymbol);
        case 7 :
        return new FourXFourTicTacToe_Player<char>(PlayerName, PlayerSymbol);
    default:
        break;
    }
}
auto Controller::selectNameAndType(string GameName, char PlayerSymbol, Player<char>*& player, int GameNumber)
{

    string playerName;
    int choice;
    GameName = selectGameName(GameNumber);
    cout << "\nWelcome to FCAI " << GameName << ". :)\n\n";

    // Set up player 1
    cout << "Enter Player" << PlayerSymbol << " name: ";
    cin >> playerName;
    cout << "Choose Player type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    if (choice == 1)
    {
        player = createHumanPlayer(GameNumber, playerName, PlayerSymbol);
    }
    else player = createComputerPlayer(GameNumber, PlayerSymbol);

}


string Controller::selectGameName(int GameNumber)
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
    default:
        break;
    }
    return GameName;
}
vector <string> Controller::getTicTacToeWords(string FileName)
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
string Controller::ReadFileName(string message)
{ 
    string FileName;
    cout << message<<endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, FileName);
    return FileName;
}
void Controller::Start()
{
    
    int GameNumber;
    Player<char>* players[2];
    PrintMainMenu();
    cin >> GameNumber;
    Board<char>* Board;
    if (GameNumber == 4)
    {
        Controller::TicTacToeWords = getTicTacToeWords(ReadFileName("please enter file name of Words: "));
         Board = createBoard(GameNumber);
        for (size_t i = 0; i < 2; i++)
        {

            selectNameAndType(selectGameName(GameNumber), i == 0 ? '1' : '2', players[i], GameNumber);
        }
    }
      
    else
    {
         Board = createBoard(GameNumber);
        for (size_t i = 0; i < 2; i++)
        {

            selectNameAndType(selectGameName(GameNumber), i==0?'X':'O', players[i], GameNumber);
        }

    }

    
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

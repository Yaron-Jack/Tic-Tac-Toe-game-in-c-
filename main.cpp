/******************************************************************************
THE WEIRD TIC TAC TOE GAME


 ******************************************************************************/

#include <iostream>
#include <string>
#include <vector>

static constexpr int const &Success = 0;
static constexpr int const &ERROR = -1;
static constexpr int const &LOWER_BOUND = 3;
static constexpr int const &UPPER_BOUND = 11;
static constexpr char const Player1Symbol = 'x';
static constexpr char const Player2Symbol = '0';

using namespace std;

/*** string multiplier operator***/
string operator*(string a, unsigned int b)
{
    string output = "";
    while (b--)
    {
        output += a;
    }
    return output;
}

void PrintTable(vector<vector<char> > &Board)
{
    for (int i = 0; i < Board.size(); ++i)
    {
        if (i == 0)
        {
            for (int j = 0; j < Board[i].size(); ++j)
            {
                cout << "Column " << j << " |";
            }
        }
    }
    string Divide = "----------";
    cout << "\n" << (Divide * Board.size()) << endl;

    for (int i = 0; i < Board.size(); ++i)
    {
        for (int j = 0; j < Board[i].size(); ++j)
        {
            cout << Board[i][j] << "        |";
        }
        cout << " Row " << i << endl;
        cout << (Divide * Board.size()) << endl;
    }
}

bool CheckInput(int PlayerColumnChoice, int PlayerRowChoice, vector<vector<char> > &Board)
{
    if (PlayerRowChoice >= 0 && PlayerColumnChoice < Board.size() && PlayerRowChoice < Board.size())
    {
        if (Board[PlayerColumnChoice][PlayerRowChoice] != Player1Symbol &&
            Board[PlayerColumnChoice][PlayerRowChoice] != Player2Symbol)
        {
            return true;
        }
        else
        {
            cout << "It's already been done" << endl;
            return false;
        }
    }
    else
    {
        cout << "Out of board range" << endl;
        return false;
    }
}

bool VictoryColumn(vector<vector<char> > &Board, char PlayerSymbol2)
{
    for (int i = 0; i < Board.size(); i++)
    {
        for (int j = 0; j < Board[i].size() - 1; j++)
        {
            if (Board[j][i] != Board[j + 1][i])
            {
                break;
            }
            if (j == Board.size() - 2 && Board[j][i] == PlayerSymbol2)
            {
                cout << "\n\tColumn Victory!" << endl;
                return true;
            }
        }
    }
    return false;
}

bool VictoryRow(vector<vector<char> > &Board, char PlayerSymbol2)
{
    for (int i = 0; i < Board.size(); i++)
    {
        for (int j = 0; j < Board[i].size()-1; j++)
        {
            if (Board[i][j] != Board[i][j+1])
            {
                break;
            }
            if (Board[i][j] == PlayerSymbol2 && j == Board.size() - 2)
            {
                cout << "\n\tRow Victory!" << endl;
                return true;
            }
        }
    }
    return false;
}

bool VictoryDiagonal1(vector<vector<char> > &Board, char PlayerSymbol2)
{
    for (int i = 0; i < Board.size() - 1; i++)
    {
        if (Board[i][i] != Board[i + 1][i + 1])
        {
            break;
        }
        if (i == Board.size() - 2 && Board[i][i] == PlayerSymbol2)
        {
            cout << "\n\tDiagonal Victory!" << endl;
            return true;
        }
    }
    return false;
}

bool VictoryDiagonal2(vector<vector<char> > &Board, char PlayerSymbol2)
{
    for (int i = 0; i < Board.size() - 1; i++)
    {
        if (Board[i][Board.size() - i - 1] != Board[i + 1][Board.size() - i - 2])
        {
            break;
        }
        if (i == Board.size() - 2 && Board[i][Board.size() - i - 1] == PlayerSymbol2)
        {
            cout << "\n\tCross Diagonal Victory!" << endl;
            return true;
        }
    }
    return false;
}


bool CheckVictory(vector<vector<char> > &Board, int Player, char PlayerSymbol, char PlayerSymbol2)
{
    if (!(VictoryColumn(Board, PlayerSymbol2)) && !(VictoryRow(Board, PlayerSymbol2)) &&
        !(VictoryDiagonal1(Board, PlayerSymbol2)) && !(VictoryDiagonal2(Board, PlayerSymbol2)))
    {
        return true;
    }
    else
    {
        cout << "\n\tHooray Player " << Player << " with the symbol of \'" << PlayerSymbol << "\' has won!\n\t" << endl;
        exit(Success);
    }
}

bool
PlayersTurn(vector<vector<char> > &Board, int Player, char PlayerSymbol, vector<pair<int, int>> &UndoTurns,
            char PlayerSymbol2)
{
    if (CheckVictory(Board, Player, PlayerSymbol, PlayerSymbol2))
    {
        int PlayerColumnChoice = 0;
        int PlayerRowChoice = 0;

        cout << "\n\tPlayer " << Player << " with the symbol \'" << PlayerSymbol << "\' Whats your choice\n"
             << flush;

        if (cin >> PlayerColumnChoice)
        {
            if (PlayerColumnChoice >= 0)
            {
                if (cin >> PlayerRowChoice && PlayerRowChoice >= 0)
                {
                    if (CheckInput(PlayerRowChoice, PlayerColumnChoice, Board))
                    {
                        Board[PlayerRowChoice][PlayerColumnChoice] = PlayerSymbol;

                        PrintTable(Board);

                        UndoTurns.push_back(pair<int, int>(PlayerRowChoice, PlayerColumnChoice));

                        return true;
                    }
                }
                else
                {
                    cout << "Bad Input" << endl;
                    exit(ERROR);
                }
            }
            else
            {
                if (PlayerColumnChoice % 2 != 0 && UndoTurns.size() >= (PlayerColumnChoice * (-1)))
                {
                    /*** Return all the values until the number -> change to ' ' -> the remaining ones to print Board Funk ***/

                    cout << "Undo function called" << endl;
                    for (int i = 0; i > PlayerColumnChoice; i--)
                    {
                        pair<int, int> Indexes = UndoTurns.back();
                        UndoTurns.pop_back();
                        Board[Indexes.first][Indexes.second] = ' ';
                    }
                    PrintTable(Board);
                    return true;
                }
                else
                {
                    cout << "Bad Input" << endl;
                    exit(ERROR);
                }
            }
        }
        else
        {
            cout << "Bad Input" << endl;
            exit(ERROR);
        }
    }
}


int main()
{
    cout << "\n\n\tTic Tac Toe in it's oddest format imaginable\n\n";


    cout << "\n\n\t Player 1 (X)  -  Player 2 (O)\n\n" << endl;

    int UserInputTable;
    cout << "\nplease enter the Board size (3 to 11): \n" << flush;


    if (cin >> UserInputTable && UserInputTable >= LOWER_BOUND && UserInputTable <= UPPER_BOUND)
    {
        cout << "\n\t Let's start! Each time a player will be selected to enter their choice of Column and Row\n\t"
                "\n\t Also a negative odd number will reverse the board accordingly\n\t"
                "\n\t In this game the loser is actually the 'winner' -you'll see " << char(1) << "\n\t"
             << endl;

        ///create a vector of vectors for the board with input each time
        vector<vector<char>> Board(UserInputTable, vector<char>(UserInputTable, ' '));

        ///create a vector of vectors for undo function
        vector<pair<int, int>> UndoTurns;

        PrintTable(Board);

        do
        {
            if (PlayersTurn(Board, 1, 'x', UndoTurns, '0'))
            {
                do
                {
                    if (PlayersTurn(Board, 2, '0', UndoTurns, 'x'))
                    {
                        break;
                    }
                } while (true);
            }
        } while (true);
    }
    else
    {
        cout << "Bad Input" << endl;
        exit(ERROR);
    }
}

/**************
 * TODO fix victory row
1.Perhaps add a timer function - ask if to play with timer and if so to write  for how many seconds(less then 60) each play
 otherwise to press 0
 -> implement timer with a if(cin >> ChoiceTimer && ChoiceTimer <= 60 && ChoiceTimer > 0)
 while(time < ChoiceTimer+1)
 {
 -game
 }

 2.Also one can enjoyably add a request that the user will choose preferred symbol
 */
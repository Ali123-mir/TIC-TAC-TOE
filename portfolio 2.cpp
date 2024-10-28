#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

vector<vector<char>> board(3, vector<char>(3, ' '));  // Tic-Tac-Toe board
enum Archetype { NONE, PALADIN, ALCHEMIST };

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << (j ? "|" : "") << (board[i][j] == ' ' ? ' ' : board[i][j]);
        }
        cout << "\n" << (i < 2 ? "-----\n" : "");
    }
    cout << "\n";
}

void resetBoard() {
    for (auto &row : board) fill(row.begin(), row.end(), ' ');
}

bool makeMove(int row, int col, char mark) {
    if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') return false;
    board[row][col] = mark;
    return true;
}

bool checkWin(char mark) {
    for (int i = 0; i < 3; ++i)
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark))
            return true;
    return (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
           (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark);
}

int main() {
    char playAgain;
    do {
        int gameType;
        resetBoard();
        cout << "Choose game type: 1. Regular  2. Battle\nChoice: ";
        cin >> gameType;

        char p1Mark, p2Mark;
        Archetype p1Type = NONE, p2Type = NONE;

        cout << "Player 1, choose your mark (A-Z, a-z): ";
        cin >> p1Mark;
        cout << "Player 2, choose your mark (A-Z, a-z): ";
        cin >> p2Mark;

        if (gameType == 2) {
            int typeChoice;
            cout << "Player 1, choose your archetype (1. Paladin, 2. Alchemist): ";
            cin >> typeChoice;
            p1Type = typeChoice == 1 ? PALADIN : ALCHEMIST;

            cout << "Player 2, choose your archetype (1. Paladin, 2. Alchemist): ";
            cin >> typeChoice;
            p2Type = typeChoice == 1 ? PALADIN : ALCHEMIST;
        }

        int turns = 0;
        bool gameOver = false;
        char currentMark = p1Mark;
        Archetype currentType = p1Type;

        while (!gameOver && turns < 9) {
            displayBoard();
            int row, col;
            cout << "Player " << (currentMark == p1Mark ? "1" : "2") << " (" << currentMark << "), enter row and column (0-2): ";
            cin >> row >> col;

            if (makeMove(row, col, currentMark)) {
                if (checkWin(currentMark)) {
                    displayBoard();
                    cout << "Player " << (currentMark == p1Mark ? "1" : "2") << " wins!\n";
                    gameOver = true;
                }
                turns++;
                currentMark = (currentMark == p1Mark) ? p2Mark : p1Mark;
                currentType = (currentType == p1Type) ? p2Type : p1Type;
            } else {
                cout << "Invalid move, try again.\n";
            }
        }
        if (!gameOver) cout << "It's a draw!\n";

        cout << "Play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}

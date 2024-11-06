#include <iostream>
using namespace std;

const int SIZE = 3;
char** createBoard() {
    char** field = new char* [SIZE];
    for (int i = 0; i < SIZE; i++) {
        field[i] = new char[SIZE];
        for (int j = 0; j < SIZE; j++) {
            field[i][j] = '+';
        }
    }
    return field;
}

void displayBoard(char** field) {
    cout << "Current board:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkWin(char** field, char symbol) {
    for (int i = 0; i < SIZE; i++) {
        if ((field[i][0] == symbol && field[i][1] == symbol && field[i][2] == symbol) || // строки
            (field[0][i] == symbol && field[1][i] == symbol && field[2][i] == symbol)) { // столбцы
            return true;
        }
    }
    if ((field[0][0] == symbol && field[1][1] == symbol && field[2][2] == symbol) ||
        (field[0][2] == symbol && field[1][1] == symbol && field[2][0] == symbol)) {
        return true;
    }
    return false;
}

bool checkDraw(int amountOfFreePlaces) {
    return amountOfFreePlaces == 0;
}

void playerMove(char** field, char symbol) {
    int x, y;
    cout << "Enter a row (0-2) for " << symbol << ": ";
    cin >> x;
    cout << "Enter a column (0-2) for " << symbol << ": ";
    cin >> y;

    while (x < 0 || x >= SIZE || y < 0 || y >= SIZE || field[x][y] != '+') {
        cout << "Invalid move. Enter a row (0-2): ";
        cin >> x;
        cout << "Enter a column (0-2): ";
        cin >> y;
    }

    field[x][y] = symbol;
}

int main() {
    char** field = createBoard();
    bool isGameOver = false;
    char symbol = 'X';
    int countOfSteps = 1;
    int amountOfFreePlaces = 9;

    while (!isGameOver) {
        displayBoard(field);

        symbol = (countOfSteps % 2 == 0) ? 'O' : 'X';
        countOfSteps++;

        playerMove(field, symbol);
        amountOfFreePlaces--;

        if (checkWin(field, symbol)) {
            displayBoard(field);
            cout << "Winner is: " << symbol << endl;
            isGameOver = true;
        }
        else if (checkDraw(amountOfFreePlaces)) {
            displayBoard(field);
            cout << "Draw" << endl;
            isGameOver = true;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        delete[] field[i];
    }
    delete[] field;
    field = nullptr;

    return 0;
}


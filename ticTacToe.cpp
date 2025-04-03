#include <iostream>
#include <limits>
#include <algorithm> // For std::max, std::min

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];
char PLAYER, AI; 

// Function to print the board
void printBoard() {
    cout << "  0 1 2\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << " ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << "|";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "  -+-+-\n";
    }
}

// Check if the board is full
bool isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Check if a player has won
char checkWinner() {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != ' ') {
            return board[i][0];
        }
    }
    // Check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] &&
            board[1][j] == board[2][j] &&
            board[0][j] != ' ') {
            return board[0][j];
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != ' ') {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != ' ') {
        return board[0][2];
    }
    return ' '; // No winner yet
}

// Minimax algorithm to determine best move
int minimax(bool isMaximizing) {
    char winner = checkWinner();
    if (winner == AI)     return  1;  // AI wins
    if (winner == PLAYER) return -1;  // Player wins
    if (isBoardFull())    return  0;  // Draw

    if (isMaximizing) {
        int bestScore = -numeric_limits<int>::max();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = AI;
                    int score = minimax(false);
                    board[i][j] = ' '; // Undo move
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = PLAYER;
                    int score = minimax(true);
                    board[i][j] = ' '; // Undo move
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

// Find the best move for AI
void bestMove() {
    int bestScore = -numeric_limits<int>::max();
    int moveX = -1, moveY = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = AI;
                int score = minimax(false);
                board[i][j] = ' '; // Undo move
                if (score > bestScore) {
                    bestScore = score;
                    moveX = i;
                    moveY = j;
                }
            }
        }
    }
    board[moveX][moveY] = AI;
}

// Resets the board to all spaces
void resetBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Main game loop
void playGame() {
    resetBoard();

    while (true) {
        printBoard();
        // Check if someone has won or it's a draw
        char winner = checkWinner();
        if (winner == PLAYER) {
            cout << "You win!\n";
            break;
        }
        if (winner == AI) {
            cout << "AI wins!\n";
            break;
        }
        if (isBoardFull()) {
            cout << "It's a draw!\n";
            break;
        }

        // Player move
        int x, y;
        cout << "Enter your move (row and column): ";
        cin >> x >> y;

        // Validate input
        if (cin.fail() || x < 0 || x >= SIZE || y < 0 || y >= SIZE || board[x][y] != ' ') {
            cin.clear(); // clear the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid move, try again!\n";
            continue;
        }

        // Place player's move
        board[x][y] = PLAYER;

        // Check for immediate game-end
        winner = checkWinner();
        if (winner != ' ' || isBoardFull()) {
            printBoard();
            break;
        }

        // AI move
        bestMove();
    }

    // Print final board state
    printBoard();
}

// Main function
int main() {
    cout << "Welcome to Tic-Tac-Toe!" << endl;

    while (true) {
        cout << "Enter your choice [X or O]: ";
        cin >> PLAYER;
        if (PLAYER == 'X' || PLAYER == 'x') {
            PLAYER = 'X';
            AI = 'O';
        } else {
            PLAYER = 'O';
            AI = 'X';
        }

        // Play a game
        playGame();

        // Ask if user wants to continue
        cout << "Enter 1 to play again, any other key to quit: ";
        int choice;
        cin >> choice;
        if (choice == 1) {
            continue;
        } else {
            break;
        }
    }
    return 0;
}

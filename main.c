// A simple C program to find maximum score that
// maximizing player can get.
#include <stdio.h>
#include <stdbool.h>

// Basic declarations
int number_of_cells = 9;
int total_calls = 0;

struct move {
    int row;
    int col;
};

char player = 'x';
char opponent = 'o';

// Hoe many moves are left on the board.
bool MovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return true;
    return false;
}

// What is the current score of the game.
// Win for X = 10
// Win for Y = -10
// Tie game = 0
int score(char b[3][3]) {
    // Check rows for a win.
    for (int row = 0; row < 3; row++) {
        if (b[row][0] == b[row][1] && b[row][1] == b[row][2]) {
            if (b[row][0] == player)
                return 10;
            else if (b[row][0] == opponent)
                return -10;
        }
    }
    // Check columns for a win.
    for (int col = 0; col < 3; col++) {
        if (b[0][col] == b[1][col] && b[1][col] == b[2][col]) {
            if (b[0][col] == player) {
                return 10;
            }
            else if (b[0][col] == opponent) {
                return -10;
            }
        }
    }
    // Check diagonals for a win.
    // Left to right
    if (b[0][0] == b[1][1] && b[1][1] == b[2][2])
    {
        if (b[0][0] == player)
            return 10;
        else if (b[0][0] == opponent)
            return -10;
    }
    // Right to left
    if (b[0][2] == b[1][1] && b[1][1] == b[2][0]) {
        if (b[0][2] == player)
            return 10;
        else if (b[0][0] == opponent)
            return -10;
    }
    return 0;

}

// Returns the optimal value a maximizer can obtain.
// Depth is current depth in game tree.
// isMax is true if current move is of maximizer (X)
int minimax(int depth, bool isMax, char board[3][3], struct move * bestMove)
{

    // See if we should keep going.
    int currentScore = score(board);
    if (currentScore == 10 || currentScore == -10) {
        return currentScore;
    }

    // How many times have we executed minimax
    ++total_calls;

    // Have we hit our search depth (In this example it is all moves possible)
    if (!MovesLeft(board))
        return currentScore;

    int currentValue;
    int bestScore;
    if (isMax) {
        // Set bestScore to lower than possible...everyting else is a better choice.
        bestScore = -100;
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col) {
                // If we have an empty square let's find out if it helps us.
                if (board[row][col] == '_') {
                    board[row][col] = player;

                    currentValue = minimax(depth + 1, false, board, bestMove);
                    // Remove the last move made.
                    board[row][col] = '_';

                    // Did we find a better move then we had?
                    if (currentValue > bestScore) {
                        bestScore = currentValue - depth;
                        bestMove->row = row;
                        bestMove->col = col;
                    }
                }
            }
    } else {
        // Set bestScore to higher than possible...everyting else is a better choice.
        bestScore = 100;
        for (int row = 0; row < 3; ++row)
            for (int col = 0; col < 3; ++col) {
                // If we have an empty square let's find out if it helps us.
                if (board[row][col] == '_') {

                    board[row][col] = opponent;

                    currentValue = minimax(depth + 1, true, board, bestMove);
                    // Remove the last move made.
                    board[row][col] = '_';

                    // Did we find a better move then we had?
                    if (currentValue < bestScore) {
                        bestScore = currentValue + depth;
                        bestMove->row = row;
                        bestMove->col = col;
                    }
                }
            }
    }
    return bestScore;
}

void findBestMove(char board[3][3]) {
    int s = -999;
    struct move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Get the best score & move possible
    s = minimax(1, true, board, &bestMove);

    printf("Best move is: row = %d col = %d\n", bestMove.row, bestMove.col);
    printf("move value: %d\n", s);

    // Make the move we just learned.
    board[bestMove.row][bestMove.col] = 'x';
    // What is the score now?
    s = score(board);
    printf("Score is: %d\n", s);
    if (s == 10) {
        printf("Computer wins\n");
    }
    else if (s == -10) {
        printf("Player wins\n");
    }
    else if (s == 0 && !MovesLeft(board)) {
        printf("Tie game\n");
    }
}

int main()
{
    // Setup a tic-tac-toe board
    char board[3][3] = {
        // An interesting board for the computer to think about.
        { '_', 'x', '_'},
        { '_', 'o', 'x'},
        { 'o', 'o', 'x'}

};

    // Given the board above what is the best move X can make.
    findBestMove(board);

    printf("Total calls: %d\n", total_calls);
    return 0;
}

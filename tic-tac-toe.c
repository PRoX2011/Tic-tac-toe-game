#include <stdio.h>
#include <stdbool.h>

#define SIZE 9

void printBoard(char board[]);
bool checkWin(char board[], char player);
bool isBoardFull(char board[]);
int getBestMove(char board[]);
int minimax(char board[], int depth, bool isMaximizing);

int main() {
    printf("Welcome to the Tic - Tac - Toe game\n");
    printf("-----------------------------------\n");

    char board[SIZE] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char player = 'X';
    char bot = 'O';

    while (true) {
        printBoard(board);

        int playerMove;
        printf("Enter your move (1-9): ");
        while (scanf("%d", &playerMove) != 1 || playerMove < 1 || playerMove > 9 || board[playerMove - 1] != ' ') {
            printf("Invalid move. Try again.\n");
            while(getchar() != '\n');
        }

        board[playerMove - 1] = player;

        if (checkWin(board, player)) {
            printBoard(board);
            printf("Congratulations! You win!\n");
            break;
        }

        if (isBoardFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }

        int botMove = getBestMove(board);
        board[botMove] = bot;

        if (checkWin(board, bot)) {
            printBoard(board);
            printf("Bot wins! Better luck next time.\n");
            break;
        }

        if (isBoardFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            break;
        }
    }

    printf("Thank you for playing!\n");
    return 0;
}

void printBoard(char board[]) {
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
}

bool checkWin(char board[], char player) {
    return (board[0] == player && board[1] == player && board[2] == player) ||
           (board[3] == player && board[4] == player && board[5] == player) ||
           (board[6] == player && board[7] == player && board[8] == player) ||
           (board[0] == player && board[3] == player && board[6] == player) ||
           (board[1] == player && board[4] == player && board[7] == player) ||
           (board[2] == player && board[5] == player && board[8] == player) ||
           (board[0] == player && board[4] == player && board[8] == player) ||
           (board[2] == player && board[4] == player && board[6] == player);
}

bool isBoardFull(char board[]) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i] == ' ') {
            return false;
        }
    }
    return true;
}

int getBestMove(char board[]) {
    int bestScore = -1000;
    int move = -1;

    for (int i = 0; i < SIZE; i++) {
        if (board[i] == ' ') {
            board[i] = 'O';
            int score = minimax(board, 0, false);
            board[i] = ' ';

            if (score > bestScore) {
                bestScore = score;
                move = i;
            }
        }
    }
    return move;
}

int minimax(char board[], int depth, bool isMaximizing) {
    if (checkWin(board, 'O')) return 10 - depth;
    if (checkWin(board, 'X')) return depth - 10;
    if (isBoardFull(board)) return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < SIZE; i++) {
            if (board[i] == ' ') {
                board[i] = 'O';
                int score = minimax(board, depth + 1, false);
                board[i] = ' ';
                bestScore = (score > bestScore) ? score : bestScore;
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < SIZE; i++) {
            if (board[i] == ' ') {
                board[i] = 'X';
                int score = minimax(board, depth + 1, true);
                board[i] = ' ';
                bestScore = (score < bestScore) ? score : bestScore;
            }
        }
        return bestScore;
    }
}

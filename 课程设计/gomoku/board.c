#include "board.h"

void initBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = EMPTY;
}

int placePiece(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player) {
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE)
        return 0;
    if (board[x][y] != EMPTY)
        return 0;
    board[x][y] = player;
    return 1;
}

int checkWin(int board[BOARD_SIZE][BOARD_SIZE], int x, int y) {
    // 当前仅为框架，后续可补全五子连珠逻辑
    int player = board[x][y];
    if (player == EMPTY) return 0;
    return 0;
}
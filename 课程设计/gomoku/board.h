#ifndef BOARD_H
#define BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#define BOARD_SIZE 15
#define EMPTY 0
#define BLACK 1
#define WHITE 2

void initBoard(int board[BOARD_SIZE][BOARD_SIZE]);
int placePiece(int board[BOARD_SIZE][BOARD_SIZE], int x, int y, int player);
int checkWin(int board[BOARD_SIZE][BOARD_SIZE], int x, int y);

#ifdef __cplusplus
}
#endif

#endif
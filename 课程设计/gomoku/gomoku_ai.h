#ifndef GOMOKU_AI_H
#define GOMOKU_AI_H

#include <utility>
#include <vector>

const int BOARD_SIZE = 15;
const int AI_PLAYER = 2;      // 白 = 电脑
const int HUMAN_PLAYER = 1;   // 黑 = 玩家

class GomokuAI {
public:
    explicit GomokuAI(int depth = 4);
    std::pair<int, int> getNextMove(int board[BOARD_SIZE][BOARD_SIZE]);

private:
    int searchDepth;
    int minimax(int board[BOARD_SIZE][BOARD_SIZE],
                int depth, int alpha, int beta, bool maximizing);
    int evaluate(int board[BOARD_SIZE][BOARD_SIZE]);
    int evalLine(int board[BOARD_SIZE][BOARD_SIZE],
                 int x, int y, int dx, int dy, int player);
    std::vector<std::pair<int, int>> generateMoves(
        int board[BOARD_SIZE][BOARD_SIZE]);
};

#endif
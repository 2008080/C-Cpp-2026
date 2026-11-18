#include "gomoku_ai.h"
#include <algorithm>
#include <climits>

static const int DIR[4][2] = {{1,0},{0,1},{1,1},{1,-1}};

GomokuAI::GomokuAI(int depth) : searchDepth(depth) {}

int GomokuAI::evalLine(int board[BOARD_SIZE][BOARD_SIZE],
                       int x, int y, int dx, int dy, int player) {
    int opp = (player == AI_PLAYER) ? HUMAN_PLAYER : AI_PLAYER;
    int cnt = 1;
    int space_before = 0, space_after = 0;

    for (int i = 1; i < 5; ++i) {
        int nx = x + dx*i, ny = y + dy*i;
        if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
        if (board[nx][ny] == player) ++cnt;
        else if (board[nx][ny] == 0 && i == 1) { space_after = 1; break; }
        else break;
    }
    for (int i = 1; i < 5; ++i) {
        int nx = x - dx*i, ny = y - dy*i;
        if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE) break;
        if (board[nx][ny] == player) ++cnt;
        else if (board[nx][ny] == 0 && i == 1) { space_before = 1; break; }
        else break;
    }
    if (cnt >= 5) return 1000000;
    switch (cnt) {
    case 4: return (space_before + space_after) ? 50000 : 5000;
    case 3: return (space_before + space_after) ? 1000  : 100;
    case 2: return (space_before + space_after) ? 100   : 10;
    case 1: return 1;
    default: return 0;
    }
}

int GomokuAI::evaluate(int board[BOARD_SIZE][BOARD_SIZE]) {
    int scoreAI = 0, scoreHuman = 0;
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == AI_PLAYER) {
                for (auto& d : DIR)
                    scoreAI += evalLine(board, i, j, d[0], d[1], AI_PLAYER);
            } else if (board[i][j] == HUMAN_PLAYER) {
                for (auto& d : DIR)
                    scoreHuman += evalLine(board, i, j, d[0], d[1], HUMAN_PLAYER);
            }
        }
    return scoreAI - scoreHuman * 2;
}

std::vector<std::pair<int,int>> GomokuAI::generateMoves(
    int board[BOARD_SIZE][BOARD_SIZE]) {
    std::vector<std::pair<int,int>> moves;
    bool mark[BOARD_SIZE][BOARD_SIZE] = {false};
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 0) continue;
            for (int di = -2; di <= 2; ++di)
                for (int dj = -2; dj <= 2; ++dj) {
                    int ni = i + di, nj = j + dj;
                    if (ni < 0 || ni >= BOARD_SIZE || nj < 0 || nj >= BOARD_SIZE) continue;
                    if (board[ni][nj] == 0 && !mark[ni][nj]) {
                        mark[ni][nj] = true;
                        moves.push_back({ni, nj});
                    }
                }
        }
    if (moves.empty()) moves.push_back({7, 7});
    return moves;
}

int GomokuAI::minimax(int board[BOARD_SIZE][BOARD_SIZE],
                      int depth, int alpha, int beta, bool maximizing) {
    if (depth == 0) return evaluate(board);

    auto moves = generateMoves(board);
    if (moves.empty()) return evaluate(board);

    if (maximizing) {
        int maxEval = INT_MIN;
        for (auto& m : moves) {
            board[m.first][m.second] = AI_PLAYER;
            int ev = minimax(board, depth - 1, alpha, beta, false);
            board[m.first][m.second] = 0;
            maxEval = std::max(maxEval, ev);
            alpha = std::max(alpha, ev);
            if (beta <= alpha) break;
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (auto& m : moves) {
            board[m.first][m.second] = HUMAN_PLAYER;
            int ev = minimax(board, depth - 1, alpha, beta, true);
            board[m.first][m.second] = 0;
            minEval = std::min(minEval, ev);
            beta = std::min(beta, ev);
            if (beta <= alpha) break;
        }
        return minEval;
    }
}

std::pair<int,int> GomokuAI::getNextMove(int board[BOARD_SIZE][BOARD_SIZE]) {
    int bestScore = INT_MIN;
    std::pair<int,int> bestMove = {7, 7};
    auto moves = generateMoves(board);

    for (auto& m : moves) {
        board[m.first][m.second] = AI_PLAYER;
        int score = minimax(board, searchDepth - 1, INT_MIN, INT_MAX, false);
        board[m.first][m.second] = 0;
        if (score > bestScore) {
            bestScore = score;
            bestMove = m;
        }
    }
    return bestMove;
}
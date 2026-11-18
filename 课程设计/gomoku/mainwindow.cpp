#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    currentPlayer(BLACK), gameOver(false), vsAI(true) {
    ui->setupUi(this);
    setFixedSize(OFFSET*2 + GRID*(BOARD_SIZE-1),
                 OFFSET*2 + GRID*(BOARD_SIZE-1));
    ai = new GomokuAI(4);
    initBoard();
}

MainWindow::~MainWindow() { delete ai; delete ui; }

void MainWindow::initBoard() {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j)
            board[i][j] = EMPTY;
    currentPlayer = BLACK;
    gameOver = false;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);
    p.fillRect(rect(), QColor(200, 150, 100));
    drawBoard(p);
    drawPieces(p);
}

void MainWindow::drawBoard(QPainter &p) {
    p.setPen(QPen(Qt::black, 2));
    for (int i = 0; i < BOARD_SIZE; ++i) {
        p.drawLine(OFFSET, OFFSET+i*GRID, OFFSET+GRID*(BOARD_SIZE-1), OFFSET+i*GRID);
        p.drawLine(OFFSET+i*GRID, OFFSET, OFFSET+i*GRID, OFFSET+GRID*(BOARD_SIZE-1));
    }
    int star[][2] = {{3,3},{7,3},{11,3},{3,7},{7,7},{11,7},{3,11},{7,11},{11,11}};
    p.setBrush(Qt::black);
    for (auto& s : star)
        p.drawEllipse(OFFSET+s[0]*GRID-3, OFFSET+s[1]*GRID-3, 6, 6);
}

void MainWindow::drawPieces(QPainter &p) {
    for (int i = 0; i < BOARD_SIZE; ++i)
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == EMPTY) continue;
            p.setBrush(board[i][j] == BLACK ? Qt::black : Qt::white);
            p.setPen(Qt::black);
            p.drawEllipse(QPoint(OFFSET+i*GRID, OFFSET+j*GRID),
                          GRID/2-2, GRID/2-2);
        }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (gameOver || event->button() != Qt::LeftButton) return;
    int x = std::round((event->x() - OFFSET) * 1.0 / GRID);
    int y = std::round((event->y() - OFFSET) * 1.0 / GRID);
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return;
    if (board[x][y] != EMPTY) return;

    board[x][y] = currentPlayer;
    update();
    if (checkWin(x, y)) return;

    if (vsAI && currentPlayer == WHITE && !gameOver)
        QTimer::singleShot(300, this, &MainWindow::onAIMove);
}

void MainWindow::onAIMove() {
    if (gameOver) return;
    auto [ax, ay] = ai->getNextMove(board);
    board[ax][ay] = WHITE;
    update();
    if (checkWin(ax, ay)) return;
    currentPlayer = BLACK;
}

bool MainWindow::checkWin(int x, int y) {
    int dir[4][2] = {{1,0},{0,1},{1,1},{1,-1}};
    int cur = board[x][y];
    for (int d = 0; d < 4; ++d) {
        int cnt = 1, dx = dir[d][0], dy = dir[d][1];
        for (int i = 1; i < 5; ++i) {
            int nx = x+dx*i, ny = y+dy*i;
            if (nx>=0 && nx<BOARD_SIZE && ny>=0 && ny<BOARD_SIZE && board[nx][ny]==cur) ++cnt;
            else break;
        }
        for (int i = 1; i < 5; ++i) {
            int nx = x-dx*i, ny = y-dy*i;
            if (nx>=0 && nx<BOARD_SIZE && ny>=0 && ny<BOARD_SIZE && board[nx][ny]==cur) ++cnt;
            else break;
        }
        if (cnt >= 5) {
            QString winner = (cur == BLACK) ? "黑棋(你)" : "白棋(电脑)";
            QMessageBox::information(this, "游戏结束", winner + "获胜！");
            gameOver = true;
            return true;
        }
    }
    currentPlayer = (cur == BLACK) ? WHITE : BLACK;
    return false;
}
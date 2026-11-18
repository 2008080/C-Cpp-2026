#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include "gomoku_ai.h"

const int GRID = 40;
const int OFFSET = GRID;
const int EMPTY = 0;
const int BLACK = 1;
const int WHITE = 2;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onAIMove();

private:
    Ui::MainWindow *ui;
    int board[BOARD_SIZE][BOARD_SIZE];
    int currentPlayer;
    bool gameOver;
    bool vsAI;
    GomokuAI *ai;

    void initBoard();
    void drawBoard(QPainter &p);
    void drawPieces(QPainter &p);
    bool checkWin(int x, int y);
};

#endif
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("五子棋 - Alpha-Beta 剪枝 AI");
    w.show();
    return a.exec();
}
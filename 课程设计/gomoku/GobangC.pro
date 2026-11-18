QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TARGET = GomokuC
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           gomoku_ai.cpp

HEADERS += mainwindow.h \
           gomoku_ai.h

FORMS += mainwindow.ui
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"gamemode.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void mouseMoveEvent(QMouseEvent *event);
     void paintEvent(QPaintEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void PersonMove();
private:
     const int TEdgeSize;
     const int TBlockSize;
     const int TBoardSize;
     const int TMarkSize;
     const int TPosDelta;
     const int TRadius;
     int ClickPosRow;
     int ClickPosCol;
     GameMode*game;

private slots:
          void AIMove();
          void Sleep();
};

#endif // MAINWINDOW_H

#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"dealinfor.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
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
     DealInfor*game;

private slots:
          void AIMove();
};

#endif // WIDGET_H

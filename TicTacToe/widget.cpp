#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include <QTimer>
#include "widget.h"
const int TBlockNum=3;
Widget::Widget(QWidget *parent)
    : TEdgeSize(30),TBlockSize(50),TRadius(18),TBoardSize(150),
      TMarkSize(10),TPosDelta(20), QWidget(parent)
{
    this->setWindowTitle("井字棋");
setFixedSize(TEdgeSize * 2 + TBlockSize * TBlockNum, TEdgeSize * 2 + TBlockSize * TBlockNum);
ClickPosRow=-1;
ClickPosCol=-1;
game=new DealInfor;
game->StartGame();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    int x=event->x();
    int y=event->y();
    //限制只能在棋盘里面落子
    if(x>TEdgeSize+TBlockSize/4&&x<TEdgeSize+TBoardSize-TBlockSize/4&&
            y>TEdgeSize+TBlockSize/4&&y<TEdgeSize+TBoardSize-TBlockSize/4 ){
        int row=(x-TEdgeSize)/TBlockSize;
        int col=(y-TEdgeSize)/TBlockSize;
        ClickPosRow=row;
        ClickPosCol=col;
    }
    else{
        ClickPosRow=-1;
        ClickPosCol=-1;
    }
  //  update();
    if(game->playerFlag==true){
        PersonMove();
        if(game->playerFlag==false)
           QTimer::singleShot(600, this, SLOT(AIMove()));
    }
}

void Widget::PersonMove()
{
    game->ActionByPerson(ClickPosRow,ClickPosCol);
    update();
}

void Widget::AIMove()
{
    game->ACtionByAI(ClickPosRow,ClickPosCol);
    update();
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    //绘制棋盘
    for(int i=0;i<TBlockNum+1;++i){
        painter.drawLine(TEdgeSize,TEdgeSize+TBlockSize*i,TEdgeSize+TBoardSize,TEdgeSize+TBlockSize*i);
        painter.drawLine(TEdgeSize+TBlockSize*i,TEdgeSize,TEdgeSize+TBlockSize*i,TEdgeSize+TBoardSize);
    }
    //绘制棋子
for(int i=0;i<TBlockNum;++i){
    for(int j=0;j<TBlockNum;++j){
        if(game->gameMapVec[i][j]==1){
             painter.setBrush(QBrush(Qt::black, Qt::Dense3Pattern));
            painter.drawEllipse(TEdgeSize+TBlockSize*i+5,
                                TEdgeSize+TBlockSize*j+5,
                                2*TRadius,2*TRadius);
        }
        else if(game->gameMapVec[i][j]==-1){
             painter.setBrush(QBrush(Qt::red, Qt::Dense3Pattern));
            painter.drawRect(TEdgeSize+TBlockSize*i+5,
                                TEdgeSize+TBlockSize*j+5,
                                2*TRadius,2*TRadius);
        }
    }
}
    //判断输赢
if(ClickPosRow!=-1&&ClickPosCol!=-1){
      QString str;
      int flag=game->isAIWin(game->gameMapVec);
      if(flag!=0)
      {
    if( game->playerFlag==false){
            str="You win!";
        }
        else {
            str="Of course,you lose!";
        }
        QMessageBox::StandardButton btnValue =
           QMessageBox::information(this, "Congratulations", str);
        if (btnValue == QMessageBox::Ok)
        {
            game->StartGame();
            ClickPosCol=ClickPosRow=-1;
        }
    }
      //判断平局
    else if(game->isDeadGame()==true){
        QMessageBox::StandardButton btnValue =
           QMessageBox::information(this, "Congratulations", "残念，draw.");
        if (btnValue == QMessageBox::Ok){
            game->StartGame();
            ClickPosCol=ClickPosRow=-1;
        }
    }
}
}

Widget::~Widget()
{

}

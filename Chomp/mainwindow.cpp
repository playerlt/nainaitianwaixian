#include "mainwindow.h"
#include<QPainter>
#include<QMouseEvent>
#include<QMessageBox>
#include <QTimer>
const int TBlockNum=6;
MainWindow::MainWindow(QWidget *parent)
    : TEdgeSize(30),TBlockSize(50),TRadius(18),TBoardSize(300),
      TMarkSize(10),TPosDelta(20)
{
    this->setWindowTitle("Chomp");
setFixedSize(TEdgeSize * 2 + TBlockSize * TBlockNum, TEdgeSize * 2 + TBlockSize * TBlockNum);
ClickPosRow=-1;
ClickPosCol=-1;
game=new GameMode;
game->StartGame();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
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

void MainWindow::PersonMove()
{
    game->ActionByPerson(ClickPosRow,ClickPosCol);
    update();
}

void MainWindow::AIMove()
{
    game->ACtionByAI(ClickPosRow,ClickPosCol);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true); // 抗锯齿
    //绘制棋盘
    for(int i=0;i<TBlockNum+1;++i){
        painter.drawLine(TEdgeSize,TEdgeSize+TBlockSize*i,TEdgeSize+TBoardSize,TEdgeSize+TBlockSize*i);
        painter.drawLine(TEdgeSize+TBlockSize*i,TEdgeSize,TEdgeSize+TBlockSize*i,TEdgeSize+TBoardSize);
    }
    //绘制饼干
    painter.setBrush(QBrush(Qt::red, Qt::Dense3Pattern));
   painter.drawEllipse(TEdgeSize+5,
                       TEdgeSize+5,
                       2*TRadius,2*TRadius);
for(int i=0;i<TBlockNum;++i){
    for(int j=0;j<TBlockNum;++j){
        if(game->gameMapVec[i][j]==0){
             painter.setBrush(QBrush(Qt::black, Qt::Dense3Pattern));
            painter.drawEllipse(TEdgeSize+TBlockSize*i+5,
                                TEdgeSize+TBlockSize*j+5,
                                2*TRadius,2*TRadius);
        }
    }
}
    //判断输赢
if(ClickPosRow!=-1&&ClickPosCol!=-1){
      QString str;
      int flag=game->isWin();
      if(flag==-1)
      {
    if( game->playerFlag==true){
            str="You win!";
        }
        else {
//QTimer::singleShot(5000, this, SLOT(Sleep()));
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
}
}
  void MainWindow::Sleep()
  {

  }
MainWindow::~MainWindow()
{

}

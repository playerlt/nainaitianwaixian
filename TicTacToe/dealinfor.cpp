#include "dealinfor.h"
//#include<algorithm>
#define max(x,y) ((x)>(y)?:(x),(y))
#define min(x,y) ((x)<(y)?:(x),(y))
extern const int TBlockNum=3;
DealInfor::DealInfor()
{
playerFlag=true;
}
void DealInfor::StartGame()
{
    gameMapVec.clear();
    playerFlag=true;
    std::vector<int> OneRow(TBlockNum,0);
    for(int i=0;i<TBlockNum;++i){
        gameMapVec.push_back(OneRow);
    }
}
void DealInfor::ActionByPerson(int&x,int&y)
{

    UpdateMap(x,y);
}

void DealInfor::ACtionByAI(int&x,int&y)
{
    int row=0,col=0;
    int score=-10;
   for(int i=0;i<TBlockNum;++i){
          for(int j=0;j<TBlockNum;++j){
               if(gameMapVec[i][j]==0){
   int tmp=minmax(0,gameMapVec,true,i,j);
   if(tmp>=score){
       score=tmp;
   row=i;
   col=j;
   }
}
}
}
      UpdateMap(row,col);
}

void DealInfor::UpdateMap(int&x,int&y)
{
    if(x<0||x>=TBlockNum||y<0||y>=TBlockNum)
        return;
    if(gameMapVec[x][y]!=0)
        return;
    //人下棋记为1，AI下棋记为-1
    if(playerFlag==true){
        gameMapVec[x][y]=1;
    }
    else{
        gameMapVec[x][y]=-1;
    }
    playerFlag=!playerFlag;
}

bool DealInfor::isDeadGame()
{
    for(int i=0;i<TBlockNum;++i){
        for(int j=0;j<TBlockNum;++j){
          if(gameMapVec[i][j]==0)
              return false;
        }
    }
    return true;
}

int DealInfor::minmax(int h,std::vector<std::vector<int>>map,bool isMax,
                      int x,int y)  //h是搜索深度，空棋盘初始深度为0，有一个棋子深度就加1
//map存储了棋盘上面的所有棋子，AI的棋子记为-1，玩家的棋子记为1,
//isMax为true时，轮到AI下子，AI要从玩家所返回的值中取最大值(max),玩家要从AI所返回的值中取最小值(min)
//因为这个分值是对AI而言的，所有AI胜利加10分，玩家胜利那么AI减10分
{
       int comp=-10;
    if(isMax==true){
        map[x][y]=-1;
        int ResentScore=isAIWin(map);
    if(h==8)
        return ResentScore;
    if(ResentScore==1)
        return 10;
        for(int i=0;i<TBlockNum;++i){
            for(int j=0;j<TBlockNum;++j){
                if(map[i][j]==0){
                    int NextScore=minmax(h+1,map,false,i,j);
                    if(NextScore==-10)  //判断出玩家胜利，返回-10,因为-10是最小的值，会被max给舍弃掉，
                      return -10;  //即这条路不能帮助AI胜利，要舍弃
                    else
                    comp=max(comp,NextScore);
                }
            }
        }
    }
    else{
        comp=10;
        map[x][y]=1;
        int ResentScore=isAIWin(map);
    if(h==8)
        return ResentScore;
    if(ResentScore==-1)
        return -10;
        for(int i=0;i<TBlockNum;++i){
            for(int j=0;j<TBlockNum;++j){
                if(map[i][j]==0){
                    int NextScore=minmax(h+1,map,true,i,j);
                    if(NextScore==10)   //判断出AI胜利，返回10
                        return 10;
                    comp=min(comp,NextScore);
                }
            }
        }
    }
    return comp;
}
int DealInfor::isAIWin(std::vector<std::vector<int>>&map)
{
    for(int i=0;i<TBlockNum;++i){
        if(map[i][0]==map[i][1]&&
                map[i][1]==map[i][2]){
            if(map[i][0]==-1)
                return 1;
        else if(map[i][0]==1)
                return -1;
        }
        if(map[0][i]==map[1][i]&&
                map[1][i]==map[2][i]){
                if(map[0][i]==-1)
                    return 1;
                else if(map[0][i]==1)
                    return -1;
        }
    }
            if(map[0][0]==map[1][1]&&
                    map[1][1]==map[2][2]){
                if(map[0][0]==-1)
                return 1;
                else if(map[0][0]==1)
                    return -1;
            }
            if(map[0][2]==map[1][1]&&
                    map[1][1]==map[2][0]){
                if(map[0][2]==-1)
                return 1;
                else if(map[0][2]==1)
                    return -1;
            }
        return 0;
}

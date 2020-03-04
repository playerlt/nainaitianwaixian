#include "gamemode.h"

GameMode::GameMode()
{
playerFlag=true;
}
extern const int TBlockNum=6;
void GameMode::StartGame()
{
    gameMapVec.clear();
    playerFlag=true;
    std::vector<int> OneRow(TBlockNum,1);
    for(int i=0;i<TBlockNum;++i){
        gameMapVec.push_back(OneRow);
    }
}
void GameMode::ActionByPerson(int&x,int&y)
{
    UpdateMap(x,y);
}

void GameMode::ACtionByAI(int&x,int&y)
{
      maxpoint_row=0,maxpoint_col=0;
       minmax(gameMapVec,true);
      UpdateMap(maxpoint_row,maxpoint_col);
}

void GameMode::UpdateMap(int&x,int&y)
{
    int row=gameMapVec.size();
    int col=gameMapVec[0].size();
    if(x<0||x>=TBlockNum||y<0||y>=TBlockNum)
        return;
    if(gameMapVec[x][y]!=1)
        return;
    //待修改
        for(int i=x;i<row;++i){
            for(int j=y;j<col;++j){
                        gameMapVec[i][j]=0;
            }
        }
    playerFlag=!playerFlag;
}

std::vector<std::vector<int>> zeromap(std::vector<std::vector<int>>map,int x,int y)
{
    for(int i=x;i<TBlockNum;++i){
        for(int j=y;j<TBlockNum;++j){
            map[i][j]=0;
        }
    }
return map;
}

int GameMode::minmax(std::vector<std::vector<int>>map,bool isMax)
{
       int comp=10;

    if(isMax==true){
        int ResentScore=isAIWin(map);
    if(ResentScore==1)
        return -10;  //人胜利，-10分
        comp=-10;

        for(int i=1;i<TBlockNum;++i){
            for(int j=0;j<TBlockNum;++j){
                if(map[i][j]==1){
                    int NextScore=minmax(zeromap(map,i,j),false);
                    if(NextScore==10){
                            maxpoint_row=i,maxpoint_col=j;
                        return 10; //人返回10，这条路可行
                    }
                        if(NextScore==-10){
                        continue;   //放弃这条路，继续搜索下一条路
                    }
                    if(comp<=NextScore){
                    maxpoint_row=i,maxpoint_col=j;
                    comp=NextScore;
                    }

                }
            }
        }

        for(int j=1;j<TBlockNum;++j){
            if(map[0][j]==1){
                int NextScore=minmax(zeromap(map,0,j),false);
                if(NextScore==10)
                {
                    maxpoint_row=0,maxpoint_col=j;
                    return 10; //人返回10，说明这条路可行
                }
                    if(NextScore==-10){
                    continue;   //放弃这条路，继续搜索下一条路
                }
               if(comp<=NextScore){
               maxpoint_row=0,maxpoint_col=j;
               comp=NextScore;
               }
            }

        }


    }
    else{
        int ResentScore=isAIWin(map);
    if(ResentScore==1)
        return 10; //AI胜利，+10分

    for(int i=1;i<TBlockNum;++i){
        for(int j=0;j<TBlockNum;++j){
            if(map[i][j]==1){
                int NextScore=minmax(zeromap(map,i,j),true);
                if(NextScore==-10)
                    return -10; //AI返回-10，说明这条路对人有利
                if(NextScore==10){
                    continue;   //放弃这条路，继续搜索下一条路
                }
                if(comp>=NextScore){
                comp=NextScore;
                }
            }
        }
    }


    for(int j=1;j<TBlockNum;++j){
        if(map[0][j]==1){
            int NextScore=minmax(zeromap(map,0,j),true);
            if(NextScore==-10)
                return -10; //AI返回-10，说明这条路对人有利
            if(NextScore==10){
                continue;   //放弃这条路，继续搜索下一条路
            }
            if(comp>=NextScore){
            comp=NextScore;
            }
        }
    }

    }
    return comp;
}
int GameMode::isAIWin(std::vector<std::vector<int>>&map)
{
    if(map.size()<1||map[0].size()<1)
        return -1;
    if(map[0][1]==0&&map[1][0]==0&&map[0][0]!=0)
        return 1;
    return 0;
}

int GameMode::isWin()
{
    if(gameMapVec[0][0]==0)
        return -1;
                return 0;
}

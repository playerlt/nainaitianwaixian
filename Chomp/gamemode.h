#ifndef GAMEMODE_H
#define GAMEMODE_H
#include<QVector>

class GameMode
{
public:
    GameMode();
    void StartGame();
    void ActionByPerson(int &x,int&y);
    void ACtionByAI(int&x,int&y);
    void UpdateMap(int&x,int&y);
    bool playerFlag;
    std::vector<std::vector<int>> gameMapVec;
    int isWin();
    int isAIWin(std::vector<std::vector<int>>&map);
private:
int minmax(std::vector<std::vector<int>>map,bool isMax);
int maxpoint_row,maxpoint_col;
};

#endif // GAMEMODE_H

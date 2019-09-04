#ifndef DEALINFOR_H
#define DEALINFOR_H
#include<QVector>

class DealInfor
{
public:
    DealInfor();
    void StartGame();
    void ActionByPerson(int &x,int&y);
    void ACtionByAI(int&x,int&y);
    void UpdateMap(int&x,int&y);
    bool playerFlag;
    std::vector<std::vector<int>> gameMapVec;
    int isAIWin(std::vector<std::vector<int>>&map);
    bool isDeadGame();
private:
int minmax(int h,std::vector<std::vector<int>>map,bool isMax,int x,int y);

};

#endif // DEALINFOR_H

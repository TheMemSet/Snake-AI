#include "AI.hpp"

char AI::update(std::vector <std::pair <int, int>>&snake,std::vector <std::pair <int, int>>&fruit)
{
//normalizacija inputa
    reverse(snake.begin(),snake.end());
    for(int i=0;i<snake.size();i++)
    {
        snake[i].xx++;snake[i].yy++;
        std::swap(snake[i].xx,snake[i].yy);
    }
    for(int i=0;i<fruit.size();i++)
    {
        fruit[i].xx++;fruit[i].yy++;
        std::swap(fruit[i].xx,fruit[i].yy);
    }
//deklaracije
    mat.clear();
    mat.resize(HI+2,std::vector<int>(WI+2,1));
    for(int i=1;i<=HI;i++)for(int j=1;j<=WI;j++)mat[i][j]=0;
    for(int i=0;i<snake.size();i++)
    {
        mat[snake[i].xx][snake[i].yy]=1;
    }
    if(fruit.size())
    {
        mat[fruit.back().xx][fruit.back().yy]=2;
    }
    else return 'U';
    std::pair<int,int> head=snake.back();
//bfs od zadnjeg voca
    bfs(mp(fruit.back().xx,fruit.back().yy));
//gdje treba skrenuti
    int maxio=-(1<<29),yoi=-1;
    for(int k=0;k<4;k++)
    {
        if(mat[head.xx+xd[k]][head.yy+yd[k]]<0
        ||mat[head.xx+xd[k]][head.yy+yd[k]]==2)
            if(maxio<mat[head.xx+xd[k]][head.yy+yd[k]])
            {
                maxio=mat[head.xx+xd[k]][head.yy+yd[k]];
                yoi=k;
            }
    }
    printf("%c ",uy[yoi]);
    if(yoi==-1)
        return 'D';
    else
        return uy[yoi];
}

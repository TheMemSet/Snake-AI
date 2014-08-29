#ifndef AI_HPP_INCLUDED
#define AI_HPP_INCLUDED

#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <queue>
#define HI 36
#define WI 64
#define xx first
#define yy second
#define mp std::make_pair

struct kockica
{
    int x,y,d;
    kockica(){}
    kockica(int _x,int _y,int _d)
    {
        x=_x;y=_y;d=_d;
    }
};

class AI
{
    char uy[4]={'R','D','U','L'};
    std::vector<std::vector<int> > mat;
    std::queue<kockica> kju;
    int xd[4]={0,1,-1,0};
    int yd[4]={1,0,0,-1};
    bool dfs(std::pair<int,int> a,int b)
    {
        if(mat[a.xx][a.yy]==1)return 0;
        if(mat[a.xx][a.yy]==2)return 1;
        mat[a.xx][a.yy]=b;
        for(int k=0;k<4;k++)
        {
            if(mat[a.xx+xd[k]][a.yy+yd[k]]!=1 && mat[a.xx+xd[k]][a.yy+yd[k]]!=b)
                if(dfs(mp(a.xx+xd[k],a.yy+yd[k]),b))return 1;
        }
        return 0;
    }
    void bfs(std::pair<int,int> _oa)
    {
        while(!kju.empty())kju.pop();
        kju.push(kockica(_oa.xx,_oa.yy,0));
        kockica tmp;
        while(!kju.empty())
        {
            tmp=kju.front();kju.pop();
            for(int k=0;k<4;k++)
            {
                if(mat[tmp.x+xd[k]][tmp.y+yd[k]]==0)
                {
                    mat[tmp.x+xd[k]][tmp.y+yd[k]]=-(tmp.d+1);
                    kju.push(kockica(tmp.x+xd[k],tmp.y+yd[k],tmp.d+1));
                }
            }
        }
    }
public:
    char update (std::vector <std::pair <int, int>>&snake,std::vector <std::pair <int, int>>&fruit);
};

#endif // AI_HPP_INCLUDED

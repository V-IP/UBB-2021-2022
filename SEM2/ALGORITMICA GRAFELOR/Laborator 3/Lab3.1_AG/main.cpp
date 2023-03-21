#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

#define inf 0x3f3f3f3f

int v,e,s;
int D[100001];
priority_queue< pair<int, int> , vector< pair<int, int> >, greater< pair<int, int> > > Q;
vector < vector < pair <int, int> > > G(100001);

void dijkstra(int s){
    for(int i=0;i<v;i++)
        D[i] = inf;
    D[s] = 0;
    Q.push({0, s});
    while(!Q.empty()){
        int dist = Q.top().first;
        s = Q.top().second;
        Q.pop();
        if(dist > D[s])
            continue;
        for(auto x:G[s])
            if(D[x.first] > dist + x.second)
            {
                D[x.first] = dist + x.second;
                Q.push({D[x.first], x.first});
            }
    }
    for(int i=0;i<v;i++)
        if(D[i] == inf)
            fout<<"INF ";
        else
            fout<<D[i]<<" ";
}

int main(int argc, char* argv[])
{
    fin>>v>>e>>s;
    int x, y, w;
    for(int i=0;i<e;i++)
    {
        fin>>x>>y>>w;
        G[x].push_back({y, w});
    }
    dijkstra(s);
    fin.close();
    fout.close();
    return 0;
}

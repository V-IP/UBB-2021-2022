#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("date.in");

int n,ma[100][100],viz[100];

void dfs(int sursa)
{
    viz[sursa]=1;
    cout<<sursa<<" ";
    for(int i=1;i<=n;i++)
        if(ma[sursa][i]==1 && viz[i]==0)
            dfs(i);
}

int main()
{
    int x,y,sursa;
    fin>>n;
    while(fin>>x>>y)
    {
        ma[x][y]=1;
        ma[y][x]=1;
    }
    cout<<"Dati un nod sursa: ";
    cin>>sursa;
    dfs(sursa);
    return 0;
}

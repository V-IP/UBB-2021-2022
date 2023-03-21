#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("in.txt");

int main()
{
    /*
    2. Fie un graf reprezentat sub o anumita forma (graful este citit dintr-un fisier). Sa se rezolve:
    a. sa se determine nodurile izolate dintr-un graf.
    b. sa se determine daca graful este regular.
    c. pentru un graf reprezentat cu matricea de adiacenta sa se determine matricea distantelor.
    d. pentru un graf reprezentat cu o matrice de adiacenta sa se determine daca este conex.
    */

    int n,m,ma[100][100],d[100],dis[100][100],x,y,i,j,ok;
    fin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            ma[i][j]=0;
            d[i]=0;
        }
    for(i=1;i<=m;i++)
    {
        fin>>x>>y;
        ma[x][y]=1;
        ma[y][x]=1;
        dis[x][y]=1;
        dis[y][x]=1;
    }

    cout<<"Nodurile izolate sunt: ";
    for(i=1;i<=n;i++)
    {
        ok=0;
        for(j=1;j<=n;j++)
            if(ma[i][j]!=0)
                ok=1;
        if(ok==0)
            cout<<i<<" ";
    }
    cout<<endl;

    for(i=1;i<=n;i++)
    {
        ok=0;
        for(j=i;j<=n;j++)
            if(ma[i][j]!=0)
                ok++;
        d[i]=ok;
    }

    int sem=1;
    for(i=1;i<=n&&sem==1;i++)
        if(d[i]!=ok)
            sem=0;
    if(sem==1)
        cout<<"Este graf regular!"<<endl;
    else
        cout<<"Nu este graf regular!"<<endl;

    for(int k=1;k<=n;k++)
        for(i=1;i<=n;i++)
            for(j=1;j<=n;j++)
                if(i!=j&&dis[i][k]&&dis[k][j])
                    if(dis[i][j]>dis[i][k]+dis[k][j] || !dis[i][j])
                        dis[i][j]=dis[i][k]+dis[k][j];


    cout<<"Matricea de distante este:"<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<dis[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;

    sem=1;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            if(i!=j && dis[i][j]==0)
                sem=0;

    if(sem==1)
        cout<<"Este conex!"<<endl;
    else
        cout<<"Nu este conex!"<<endl;

    return 0;
}

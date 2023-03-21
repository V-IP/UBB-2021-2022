#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("date.in");


struct Punct{
    int x,y;
};

char ma[100][100];
int n=21,m=41,k=0,v=0;
Punct stiva[100],viz[100];
Punct start,curent,urm;

void find_s()
{
    int sem=0;
    for(int i=0;i<n&&sem==0;i++)
        for(int j=0;j<m&&sem==0;j++)
            if (ma[i][j]=='S')
            {
                start.x=i;
                start.y=j;
                sem=1;
            }
}

bool notViz(Punct nod)
{
    for(int i=1;i<=v;i++)
        if(viz[i].x==nod.x&&viz[i].y==nod.y)
            return false;
    return true;
}

bool next()
{
    int i=curent.x;
    int j=curent.y;
    Punct nod;
    nod.x=i+1;
    nod.y=j;
    //incerc sa merg in jos
    if(ma[i+1][j]!='1'&&i+1<n&&notViz(nod))
    {
        urm.x=i+1;
        urm.y=j;
        return true;
    }
    nod.x=i;
    nod.y=j+1;
    //incerc sa merg la dreapta
    if(ma[i][j+1]!='1'&&j+1<m&&notViz(nod))
    {
        urm.x=i;
        urm.y=j+1;
        return true;
    }
    nod.x=i-1;
    nod.y=j;
    //incerc sa merg in sus
    if(ma[i-1][j]!='1'&&i-1>=0&&notViz(nod))
    {
        urm.x=i-1;
        urm.y=j;
        return true;
    }
    nod.x=i;
    nod.y=j-1;
    //incerc sa merg la stanga
    if(ma[i][j-1]!='1'&&j-1>=0&&notViz(nod))
    {
        urm.x=i;
        urm.y=j-1;
        return true;
    }
    return false;
}

void labirint()
{
    find_s();
    curent = start;
    stiva[++k]=start;
    viz[++v] = start;
    while(ma[curent.x][curent.y] != 'F')
    {
        if(next()==true)
        {
            curent = urm;
            viz[++v]=curent;
            stiva[++k]=curent;
        }
        else
            curent=stiva[--k];
    }
}

int main()
{
    int i;
    for(i=0;i<n;i++)
        fin.getline(ma[i],100);
    labirint();
    for(int i=2;i<k;i++)
        ma[stiva[i].x][stiva[i].y]='P';
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout<<ma[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

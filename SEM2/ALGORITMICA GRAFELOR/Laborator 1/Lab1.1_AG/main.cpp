#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("in.txt");

int main()
{
    /*
    1. Fie un fisier ce contine un graf neorientat reprezentat sub forma: prima linie contine numarul nodurilor iar urmatoarele randuri muchiile grafului.
    Sa se scrie un program in C/C++ care sa citeasca fisierul si sa reprezinte/stocheze un graf folosind matricea de adiacenta, lista de adiacenta
    si matricea de incidenta. Sa se converteasca un graf dintr-o forma de reprezentare in alta.
    Fisier -> matrice de adiacenta -> lista adiacenta -> matrice de incidenta -> matrice de adiacenta -> verificam daca ii exact ca la inceput

    exemplu fisier
    in.txt
    4
    1 2
    3 4
    2 3
    4 2
    */

    int n,ma[100][100],la[100][100],mi[100][100],manoua[100][100],x,y,i,j,m=0;
    fin>>n;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
        {
            ma[i][j]=0;
            la[i][j]=0;
            mi[i][j]=0;
            manoua[i][j]=0;
        }
    while(fin>>x>>y)
    {
        m++;
        ma[x][y]=1;
        ma[y][x]=1;
    }

    cout<<"Matricea de adiacenta este:"<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<ma[i][j]<<" ";
        cout<<endl;
    }

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            if(ma[i][j]==1)
                la[i][j]=j;
    }

    cout<<"Lista de adiacenta este:"<<endl;
    for(i=1;i<=n;i++)
    {
        cout<<i<<": ";
        for(j=1;j<=n;j++)
            if(la[i][j]!=0)
                cout<<la[i][j]<<" ";
        cout<<endl;
    }

    x=0;
    for(i=1;i<=n;i++)
        for(j=i;j<=n;j++)
            if(la[i][j]!=0)
            {
                mi[i][++x]=1;
                mi[j][x]=1;
            }

    cout<<"Matricea de incidenta este:"<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=m;j++)
            cout<<mi[i][j]<<" ";
        cout<<endl;
    }

    for(j=1;j<=m;j++)
    {
        x=y=0;
        for(i=1;i<=n;i++)
            if(mi[i][j]!=0)
            {
                if(x==0)
                    x=i;
                else
                    y=i;
            }
        manoua[x][y]=1;
        manoua[y][x]=1;
    }

    cout<<"Matricea noua de adiacenta este:"<<endl;
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<manoua[i][j]<<" ";
        cout<<endl;
    }

    int sem=1;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
            if(ma[i][j]!=manoua[i][j])
                sem=0;
    if(sem==1)
        cout<<endl<<"Matricile de adiacenta convin!"<<endl;
    else
        cout<<endl<<"Matricile de adiacenta nu coincid!"<<endl;

    return 0;
}

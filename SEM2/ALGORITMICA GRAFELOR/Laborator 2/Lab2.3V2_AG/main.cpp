#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;
ifstream fin("date.in");
int di[4] = {0,0,1,-1};
int dj[4] = {1,-1,0,0};
char a[180][180];
int n=21,m=41,dist[180][180];
int startx,starty,stopx,stopy;
queue < pair < int, int > > coada;

//caut punctul de plecare si oprire
void find_SandF()
{
    int semS=0,semF=0;
    for(int i=0;i<n&&(semS==0||semF==0);i++)
        for(int j=0;j<m&&(semS==0||semF==0);j++)
        {
            if (a[i][j]=='S')
            {
                startx=i;
                starty=j;
                semS=1;
            }
            if (a[i][j]=='F')
            {
                stopx=i;
                stopy=j;
                semF=1;
            }
        }
}

//verific daca pozitia curenta este valida
int valid(int i, int j)
{
    if(i<0||j<0||i>n-1||j>m-1)
        return 0;
    if(a[i][j]=='1')
        return 0;
    return 1;
}

//lucrez cu LEE pe o matrice de distante fiindca LEE opereaza doar cu lungimi
void LEE()
{
    int i,j,i_urmator,j_urmator;
    dist[startx][starty]=1;
    coada.push(make_pair(startx,starty));
    while(!coada.empty())
    {
        i=coada.front().first;
        j=coada.front().second;
        coada.pop();
        for(int directie=0;directie<4;directie++)
        {
            i_urmator=i+di[directie];
            j_urmator=j+dj[directie];
            if(valid(i_urmator, j_urmator)&&!dist[i_urmator][j_urmator])
            {
                dist[i_urmator][j_urmator]=dist[i][j]+1;
                coada.push(make_pair(i_urmator, j_urmator));
            }
        }
    }
}

//aceasta functie imi ia matricea de distante si o parcurg de la final pentru a pune "P" pe pozitiile unde este drumul minim
//fiindca in matricea de distante am pe toate pozitiile un nr int fiind distanta din S pana in acel punct (chit ca e corect drumul sau nu)
void antiLEE()
{
    int i,j,i_urmator,j_urmator;
    coada.push(make_pair(stopx,stopy));
    while(!coada.empty())
    {
        i=coada.front().first;
        j=coada.front().second;
        coada.pop();
        for(int directie=0;directie<4;directie++)
        {
            i_urmator=i+di[directie];
            j_urmator=j+dj[directie];
            if(valid(i_urmator, j_urmator)&&dist[i_urmator][j_urmator]==dist[i][j]-1)
            {
                a[i_urmator][j_urmator]='P';
                coada.push(make_pair(i_urmator, j_urmator));
                break;
            }
        }
    }
}

int main()
{
    for(int i=0;i<n;i++)
        fin.getline(a[i],180);
    find_SandF();
    LEE();
    antiLEE();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

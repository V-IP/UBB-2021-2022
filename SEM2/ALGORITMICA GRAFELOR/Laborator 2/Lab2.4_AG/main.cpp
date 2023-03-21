#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("date.in");

int n,m,k,i,j,a[100][100],x[100],v[100];

int bfs(int sursa)
{
  int i,k,st,dr;
  st=dr=1;
  x[1]=sursa;
  v[sursa]=0;
  while(st<=dr)
  {
    k=x[st++];
    for(i=1;i<=n;i++)
      if(sursa!=i && v[i]==0 && a[k][i]==1)
      {
        v[i]=v[k]+1;
        x[++dr]=i;
      }
  }
  return dr;
}

int main()
{
    int sursa;
    fin>>n>>m;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            fin>>a[i][j];
    cout<<"Dati un nod sursa:";
    cin>>sursa;
    bfs(sursa);
    for(i=1;i<=n;i++)
        if(v[i])
            cout<<"Din nodul sursa:"<<sursa<<" pana la nodul "<<i<<" este distanta "<<v[i]<<endl;
        else
            if(i!=sursa)
                cout<<"Din nodul sursa:"<<sursa<<" pana la nodul "<<i<<" este distanta infinit"<<endl;

}

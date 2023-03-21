#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("date.in");

int i,j,n,ma[100][100],tranz[100][100],v[100],x[100];

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
      if(sursa!=i && v[i]==0 && ma[k][i]==1)
      {
        v[i]=v[k]+1;
        x[++dr]=i;
      }
  }
}

int main()
{
    int sursa;
    fin>>n;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            fin>>ma[i][j];
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            v[j]=0;
        bfs(i);
        for(j=1;j<=n;j++)
            if(v[j]!=0 || i==j)
                tranz[i][j]=1;
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
            cout<<tranz[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}

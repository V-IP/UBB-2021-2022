#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("graf.txt");

int n,ma[100][100],parinti[100],costuri[100],coada[100];

void Moore(int sursa)
{
    int i,k,st,dr;
    st=dr=1;
    costuri[sursa]=0;
    coada[1]=sursa;
    for(i=1;i<=n;i++)
        if(i!=sursa)
            costuri[i]=999999999;
    while(st<=dr)
    {
        k=coada[st++];
        for(i=1;i<=n;i++)
            if(ma[k][i]==1 && costuri[i]==999999999)
            {
                parinti[i]=k;
                costuri[i]=costuri[k]+1;
                coada[++dr]=i;
            }

    }
}

int main()
{
    int sursa,x,y;
    fin>>n;
    while(fin>>x>>y)
    {
        ma[x][y]=1;
    }
    cout<<"!!! i = infinity\nDati un nod sursa: ";
    cin>>sursa;
    Moore(sursa);
    for(int i=1;i<=n;i++)
        if(costuri[i]==999999999)
            cout<<"i ";
        else
            cout<<costuri[i]<<" ";
    cout<<endl;
    for(int i=1;i<=n;i++)
        if(parinti[i]==0)
            cout<<"- ";
        else
            cout<<parinti[i]<<" ";
    return 0;
}

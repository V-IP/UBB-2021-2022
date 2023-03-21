#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>

using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

const int maxim = 4e5+1;

int n,m,s,cost_sort[maxim],comp_conexa[maxim],x[maxim],y[maxim],c[maxim];
vector<int> arbore;

int grupa(int i)
{
	if (comp_conexa[i] == i) return i;
	comp_conexa[i] = grupa(comp_conexa[i]);
	return comp_conexa[i];
}

void reuniune(int i,int j)
{
	comp_conexa[grupa(i)] = grupa(j);
}

bool cmp_function(int i,int j)
{
	return c[i]<c[j];
}

int main(int argc,char* argv[])
{
	fin>>n>>m;
    int i;
	for(i=1;i<=m;i++)
	{
		fin>>x[i]>>y[i]>>c[i];
		cost_sort[i] = i;
	}
	for(i=1;i<=n;i++)
        comp_conexa[i] = i;
	sort(cost_sort+1,cost_sort+m+1,cmp_function);
	for(i=1;i<=m;i++)
	{
		if (grupa(x[cost_sort[i]])!=grupa(y[cost_sort[i]]))
		{
			s+=c[cost_sort[i]];
			reuniune(x[cost_sort[i]],y[cost_sort[i]]);
			arbore.push_back(cost_sort[i]);
		}
	}
	fout<<s<<endl;
	fout<<n-1<<endl;
	sort(arbore.begin(),arbore.end());
	for(i=0;i<n-1;i++)
        fout<<x[arbore[i]]<<" "<<y[arbore[i]]<<endl;
    fin.close();
    fout.close();
	return 0;
}

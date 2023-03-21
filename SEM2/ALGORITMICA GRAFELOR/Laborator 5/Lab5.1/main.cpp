#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");

#define NMAX 1000
#define INF 0x3f3f3f3f

int C[NMAX][NMAX];
int F[NMAX][NMAX];
int P[NMAX];
vector<int> G[NMAX];
int N, M;
int viz[NMAX];

int BF()
{
	queue<int> Q;
    Q.push(1);
	memset(viz, 0, sizeof(viz));
	viz[1] = 1;
	while(!Q.empty())
	{
	    int nod=Q.front();
	    Q.pop();
        if (nod == N)
            continue;
		for (auto V : G[nod])
			{
				if (C[nod][V] == F[nod][V] || viz[V])
                    continue;
				viz[V] = 1;
				Q.push(V);
				P[V] = nod;
			}
	}
	return viz[N];
}

int main()
{
	int i, flow, fmin, x, y, z;

	fin>>N>>M;

	for (i = 1; i <= M; i++)
	{
		fin>>x>>y>>z;
		x++; y++;
		C[x][y] += z;
		G[x].push_back(y);
		G[y].push_back(x);
	}
    flow=0;
    do {
		for (auto nod : G[N])
		{
			if (F[nod][N] == C[nod][N] || !viz[nod])
                continue;
			P[N] = nod;

			fmin = INF;
			for (nod = N; nod != 1; nod = P[nod])
				fmin = min(fmin, C[ P[nod] ][nod] - F[ P[nod] ][nod]);

			if (fmin == 0)
                continue;

			for (nod = N; nod != 1; nod = P[nod])
			{
				F[ P[nod] ][nod] += fmin;
				F[nod][ P[nod] ] -= fmin;
			}

			flow += fmin;
		}
    }while(BF());
	fout<<flow;
	return 0;
}

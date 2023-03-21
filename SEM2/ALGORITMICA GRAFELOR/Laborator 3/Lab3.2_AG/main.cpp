#include <fstream>
#include <vector>
#include <deque>
#include <queue>
#include <iostream>
#include <set>
#include <tuple>
#include <algorithm>

using namespace std;

const int inf = 1e9;
const int NMAX = 5e4 + 10;
vector < pair < int, int > > v[NMAX];
int dist[NMAX], was[NMAX];

int dist2[NMAX];
bool viz[NMAX];

vector < tuple < int, int, int > > weights;

int main() {
	ifstream f("date.in");
	ofstream g("date.out");
	int n, m;
	f >> n >> m;
	while (m--) {
		int x, y, z;
		f >> x >> y >> z;
		x++;
		y++;
		v[x].push_back({ y,z });
	}

	for (int i = 1; i <= n; i++) {
		v[0].push_back({ i, 0 });
		dist[i] = inf;
	}

	deque < int > q;
	q.push_back(0);
	while (!q.empty()) {
		int node = q.front();
		q.pop_front();

		for(auto it : v[node])
			if (dist[it.first] > dist[node] + it.second) {
				dist[it.first] = dist[node] + it.second;
				q.push_back(it.first);
				was[it.first]++;
				if (was[it.first] == 100 * n) {
					g << -1;
					return 0;
				}
			}
	}

	for (int i = 1; i <= n; i++)
		for (auto& it : v[i]) {
			it.second += dist[i] - dist[it.first];
			weights.push_back({i, it.first, it.second});
		}

    sort(weights.begin(), weights.end());

    for(auto it : weights){
        int x = get<0>(it);
        int y = get<1>(it);
        int z = get<2>(it);

        g << x - 1 << " " << y - 1 << " " << z << "\n";
    }

    for(int j = 1 ; j <= n ; j++){
        for (int i = 1; i <= n; i++){
            dist2[i] = inf;
            viz[i] = 0;
        }
        dist2[j] = 0;
        priority_queue < pair < int, int > > d;
        d.push({ 0, j });
        while (!d.empty()) {
            int node = d.top().second;
            d.pop();

            if (viz[node])
                continue;
            viz[node] = 1;

            for (auto it : v[node])
                if (dist2[it.first] > dist2[node] + it.second) {
                    dist2[it.first] = dist2[node] + it.second;
                    d.push({ -dist2[it.first], it.first });
                }
        }
        for (int i = 1; i <= n; i++){
            int ans = dist2[i] - dist[j] + dist[i];
            if(ans >= inf)
                g << "INF ";
            else
                g << ans << " " ;
        }
        g << "\n";
    }


	return 0;
}

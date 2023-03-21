#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

#define MAX_V 101000
#define MAX_E 501000

using namespace std;
ifstream fin( "date.in" );
ofstream fout( "date.out" );

bool used[MAX_E];
pair <int, int> edge[MAX_E];
vector <int> edges[MAX_V];
stack <int> st;
vector <int> ans;

int main() {

    int V, E, e,x, y, i;

    fin >> V >> E;
    for ( i = 0; i < E; i++ ) {
        fin >> x >> y;
        x--;
        y--;

        edge[i] = { x, y };
        edges[x].push_back( i );
        edges[y].push_back( i );
        used[i] = false;
    }

    x = 0;
    while ( x < V && edges[x].size() % 2 == 0 )
        x++;
    if ( x < V ) {
        fout << -1;
        return 0;
    }

    st.push( 0 );
    while ( !st.empty() ) {
        x = st.top();

        if ( edges[x].size() ) {
            e = edges[x].back();
            edges[x].pop_back();
            if ( !used[e] ) {
                used[e] = true;
                if ( x == edge[e].second )
                    st.push(edge[e].first);
                else
                    st.push(edge[e].second);
            }
        } else {
            ans.push_back( x + 1 );
            st.pop();
        }
    }

    for ( i = 0; i < ans.size() - 1; i++ )
        fout << ans[i] << " ";

    return 0;
}

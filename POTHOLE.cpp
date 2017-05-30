#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <cassert>
using namespace std;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> Graph;
typedef long long ll;

#define MAX_V 205 // enough for sample graph in Figure 4.24/4.25/4.26/UVa 259
#define INF 100000000

int mf, f, s, t;                          // global variables
vi p;
Graph AdjList;
map<ii, int> res_flow;

void augment(int v, int minEdge) {     // traverse BFS spanning tree from s to t
    if (v == s) { 
        f = minEdge; 
        return; 
    }  // record minEdge in a global variable f
    else if (p[v] != -1) { 
        augment(p[v], min(minEdge, res_flow[ make_pair(p[v], v) ])); // recursive
        res_flow[ make_pair(p[v], v) ] -= f; 
        res_flow[ make_pair(v, p[v]) ] += f;
    }// update
}

int T, N, neighs, v;
int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        AdjList.assign(N + 1, vii());
        for (int i = 1; i < N; i++) {
            scanf("%d", &neighs);
            for (int j = 0; j < neighs; j++) {
                scanf("%d", &v);
                AdjList[i].push_back( make_pair(v, 0) );
                AdjList[v].push_back( make_pair(i, 0) );
                res_flow[ make_pair(i,v) ] = (i == 1 || v == N) ? 1 : INF;
                res_flow[ make_pair(v, i) ] = 0;
            }
        }
        s = 1; t = N;
        mf = 0;       
        while (1) {        
              f = 0;
              // run BFS, compare with the original BFS shown in Section 4.2.2
              vi dist(N + 1, INF); dist[s] = 0; queue<int> q; q.push(s);
              p.assign(N + 1, -1);      
              while (!q.empty()) {
                    int u = q.front(); q.pop();
                    if (u == t) break; 
                    for (int v = 0; v < AdjList[u].size(); v++) { 
                        int nei = AdjList[u][v].first;
                        if (res_flow[ make_pair(u,  nei) ] > 0 && dist[nei] == INF) {
                            dist[nei] = dist[u] + 1, q.push(nei), p[nei] = u;
                        }
                    }
              }
              augment(t, INF);
              if (f == 0) break;
              mf += f;
        }
        printf("%d\n", mf);                              // this is the max flow value
        p.clear();
        AdjList.clear();
    }


    return 0;
}

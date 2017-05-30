// 2009-12-25
// Intergalactic Map: the better solution (credit to Hanson)
// Idea: starting from Tatooine, find two paths, one to Naboo, and one to
// Coruscant, such that no edge is used twice.
// TODO: Is it obvious that this algorithm is correct? :/
#include <iostream>
#include <vector>
#include <bitset>
#include <cstdio>
using namespace std;
vector<pair<int,bool> > adj[30012];
bitset<30012> vis;
bool dfs(int src,int dest) {
    int i;
    if (src == dest) return true;
    if (vis[src]) return false;
    vis[src]=true;
    for (i=0; i<adj[src].size(); i++)
        if (adj[src][i].second) {
            adj[src][i].second=false;
            if (dfs(adj[src][i].first,dest))
                return true;
            else
                adj[src][i].second=true;
        }
    return false;
}

int main() {
    int T,i,V,E,x,y;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &V, &E);
        for (i=1; i<=V; i++)
            adj[i].clear();
        while (E--) {
            scanf("%d %d", &x, &y);
            if (x<=0||y<=0||x>V||y>V) continue;
            adj[x].push_back(make_pair(y,true));
            adj[y].push_back(make_pair(x,true));
        }
        vis.reset();
        if (!dfs(2,1))
            printf("NO\n");
        else {
            vis.reset();
            if (dfs(2,3))
                printf("YES\n");
            else
                printf("NO\n");
        }
    }
    return 0;
}

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>
#define ROOT 0
#define DFS_WHITE -1
#define MAX 10005
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef vector<vii> vvi;

int N, test, dfsCounter, T[MAX], dfsNumber[MAX], cost[MAX], level[MAX];
vvi AdjList;
int P[MAX][20];

void process() {
    int i, j;

    for (int i = 0; i < N; i++)
        for (int j = 0; 1 << j < N; j++)
            P[i][j] = -1;

    for (int i = 0; i < N; i++) P[i][0] = T[i];

    for (int j = 1; 1 << j < N; j++)
        for (int i = 0; i < N; i++)
            if (P[i][j-1] != -1) 
                P[i][j] = P[ P[i][j-1] ][j-1];
            else 
                assert(false);

}

int query(int p, int q) {
    if (level[p] < level[q]) 
        swap(p, q);

    int log;
    for (log = 1; 1 << log <= level[p]; log++);
    log--;

    for (int i = log; i >= 0; i--)
        if (level[p] - (1 << i) >= level[q])
            p = P[p][i];

    if (p == q) return p;

    for (int i = log; i >= 0; i--) {
        if (P[p][i] != -1 && P[p][i] != P[q][i]) {
            p = P[p][i]; 
            q = P[q][i];
        }
    }

    return T[p];
}

void dfs(int u, int l) {
    dfsNumber[u] = dfsCounter++;
    level[u] = l;
    for (int i = 0; i < AdjList[u].size(); i++) {
        int v = AdjList[u][i].first;
        int w = AdjList[u][i].second;
        if (dfsNumber[v] == DFS_WHITE) {
            cost[v] = cost[u] + w; 
            T[v] = u;  //u is parent of v
            dfs(v, l + 1);
        }
    }
}

int dist(int a, int b) {
    return cost[a] + cost[b] - 2 * cost[ query(a, b) ];
}

int kth(int a, int b, int k) {
    int lca = query(a, b);
    int z = level[a] - level[lca] + 1;
    if (k == z) return lca;
    if (k > z) swap(a, b);

    int level_k = level[lca] + abs(k - z);

    int log;
    for (log = 1; (1 << log) <= level[a]; log++);
    log--;

    for (int i = log; i >= 0; i--)
        if (level[a] - (1 << i) >= level_k)
            a = P[a][i];

    return a;
}

int main(void) {
    cin >> test;
    while (test--) {
        cin >> N;
        assert(N < MAX);
        dfsCounter = 0;

        memset(T, ROOT, sizeof(T));
        memset(dfsNumber, DFS_WHITE, sizeof(dfsNumber));
        memset(cost, 0, sizeof(cost));
        memset(level, 0, sizeof(level));
        AdjList.assign(N, vii());

        for (int i = 0; i < N - 1; i++) {
            int a, b, c; 
            cin >> a >> b >> c;
            a--; b--;
            AdjList[a].push_back( ii(b, c) );
            AdjList[b].push_back( ii(a, c) );
        }

        dfs(ROOT, 0);
        process();

        while (1) {
            int a, b, c;
            string operation;
            cin >> operation;
            if (operation == "DONE") break;
            if (operation == "DIST") {
                cin >> a >> b;
                a--; b--;
                cout << dist(a, b) << endl;
            } else {
                cin >> a >> b >> c;
                a--; b--;
                cout << kth(a, b, c) + 1 << endl;
            }
        }
        cout << endl;

        AdjList.clear(); 
    }
    return 0;
}

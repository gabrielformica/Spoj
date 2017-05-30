#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
#include <vector>
#include <utility>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <vector>
#include <cassert>

#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)
#define ALL(container) (container).begin(), (container).end()
#define pb push_back
#define eb emplace_back
using namespace std;

const int ms = 10100;
const int logms = 15;
vector< vector<int> > adj;
vector< vector<int> > cost;
vector< vector<int> > arc;
int p[ms][logms], level[ms], subsize[ms], dfsId;
int otherEnd[ms];
int chainHead[ms], chainSize[ms], chainPos[ms], chainInd[ms], chainNo;
int posInBase[ms];
int baseArray[ms], st[ms * 6];
int ptr;
char str[20];
int test, N;

int left(int x) { return x << 1; }
int right(int x) { return (x << 1) + 1; }
int make_tree(int node, int L, int R) {
    if (L == R) return st[node] = baseArray[L];
    int c1 = make_tree(left(node), L, (L + R) / 2);
    int c2 = make_tree(right(node), (L + R) / 2 + 1, R);
    return st[node] = max(c1, c2);
}

int query(int node, int L, int R, int i, int j) {
    if (L > j || R < i) return -1;
    if (L >= i && R <= j) return st[node];
    int lr = query(left(node), L, (L + R) / 2, i, j);
    int rr = query(right(node), (L + R) / 2 + 1, R, i, j);
    return max(lr, rr);
}

void update(int node, int L, int R, int x, int val) {
    if (L > x || R < x) return; 
    if (L == R && L == x) {
        st[node] = val;
        return;
    }
    update(left(node), L, (L + R) / 2, x, val);
    update(right(node), (L + R) / 2 + 1, R, x, val);
    st[node] = max(st[left(node)], st[right(node)]);
}

void change(int u, int val) {
    int node = otherEnd[u];
    update(1, 0, ptr-1, posInBase[node], val);
}

int LCA(int u, int v) {
    if (level[u] < level[v]) swap(u, v);
    int log; 
    for (log = 1; 1 << log <= level[u]; log++);
    log--;
    for (int i = log; i >= 0; i--)
        if ( level[u] - (1 << i) >= level[v]) 
            u = p[u][i];
    if (u == v) return u;
    for (int i = logms - 1; i >= 0; i--) if (p[u][i] != p[v][i]) {
        u = p[u][i];
        v = p[v][i];
    }
    return p[u][0];
}

int query_up(int u, int v) {
    if (u == v) return 0;
    int uchain, vchain = chainInd[v], ans = -1;
    while (1) {
        uchain = chainInd[u];
        if (uchain == vchain) {
            if (u == v) break;
            int tmp = query(1, 0, ptr-1, posInBase[v]+1, posInBase[u]);
            if (tmp > ans) ans = tmp;
            break;
        }
        int tmp = query(1, 0, ptr-1, posInBase[chainHead[uchain]], posInBase[u]);
        if (tmp > ans) ans = tmp;
        u = chainHead[uchain];
        u = p[u][0];
    }
    return ans;
}

void query(int u, int v) {
    int lca = LCA(u, v);
    int ans = query_up(u, lca);
    int tmp = query_up(v, lca);
    if (tmp > ans) ans = tmp;
    printf("%d\n", ans);
}



void hdl(int cur, int ncost, int prev) {
    if (chainHead[chainNo] == -1) chainHead[chainNo] = cur;
    chainInd[cur] = chainNo;
    chainPos[cur] = chainSize[chainNo]; 
    chainSize[chainNo]++;
    posInBase[cur] = ptr;
    baseArray[ptr++] = ncost;
    

    if (subsize[cur] == 1) return;

    int ind = -1, newcost = -1, imax = -1;
    for (int i = 0; i < adj[cur].size(); i++) {
        if (adj[cur][i] == prev) continue;
        if (subsize[ adj[cur][i] ] > imax) {
            imax = subsize[ adj[cur][i] ];
            ind = i;
            newcost = cost[cur][i];
        }
    }
    hdl(adj[cur][ind], newcost, cur);
    for (int i = 0; i < adj[cur].size(); i++) {
        if (adj[cur][i] == prev) continue;
        if (i != ind) {
            chainNo++;
            hdl(adj[cur][i], cost[cur][i], cur);
        }
    }
}

void dfs(int node, int prev, int _depth) {
    p[node][0] = prev;
    level[node] = _depth;
    subsize[node] = 1;
    for (int i = 0; i < adj[node].size(); i++) {
        if (adj[node][i] != prev) {
            otherEnd[ arc[node][i] ] = adj[node][i];
            dfs(adj[node][i], node, _depth + 1);
            subsize[node] += subsize[ adj[node][i] ];
        }
    }
}

void clear() {
    memset(p, -1, sizeof(p));
    memset(level, 0, sizeof(level));
    memset(subsize, 0, sizeof(subsize));
    memset(otherEnd, -1, sizeof(otherEnd));
    memset(chainHead, -1, sizeof(chainHead));
    memset(chainSize, 0, sizeof(chainSize));
    memset(chainPos, 0, sizeof(chainPos));
    memset(chainInd, 0, sizeof(chainInd));
    memset(posInBase, 0, sizeof(posInBase));
    memset(baseArray, 0, sizeof(baseArray));
    memset(st, 0, sizeof(st));
    chainNo = ptr = dfsId = 0;
}

int main() {
    ri(test);
    while (test--) {
        clear();
        ri(N);
        adj.assign(N + 1, vector<int>());
        cost.assign(N + 1, vector<int>());
        arc.assign(N + 1, vector<int>());
        FOR(i, N-1) {
            int a, b, c; rii(a, b); ri(c); 
            assert(a <= N);
            assert(b <= N);
            a--; b--;
            adj[a].push_back(b); 
            adj[b].push_back(a); 

            cost[a].push_back(c);
            cost[b].push_back(c);

            arc[a].push_back(i);
            arc[b].push_back(i);
        }
        dfs(0, -1, 0); 
        hdl(0, -1, -1);
        make_tree(1, 0, ptr-1);

        for (int j = 1; j < logms; j++)
            for (int i = 0; i < N; i++)
                if (p[i][j - 1] != -1)
                    p[i][j] = p[ p[i][j-1] ][j - 1];

        while (1) {
            scanf("%s", str);
            if (str[0] == 'D') break;
            int a, b; rii(a, b);
            if (str[0] == 'C') change(a-1, b);
            else query(a-1, b-1);
        }

    }
    return 0;
}

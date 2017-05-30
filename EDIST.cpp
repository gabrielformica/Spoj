#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi dist;
int T, N, M;
string a, b;

void set_min(int i, int j, int cost) {
    int deletion = dist[i - 1][j] + 1;
    int insertion = dist[i][j - 1] + 1;
    int substitution = dist[i - 1][j - 1] + cost;
    if (deletion <= insertion && deletion <= substitution) 
        dist[i][j] = deletion;
    else if (insertion <= deletion && insertion <= substitution) 
        dist[i][j] = insertion;
    if (substitution <= insertion && substitution <= deletion) 
        dist[i][j] = substitution;
}

void levenshtei() {
    for (int i = 0; i <= N; i++) dist[i][0] = i;
    for (int i = 0; i <= M; i++) dist[0][i] = i;

    int cost = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cost = (a[i] == b[j]) ? 0 : 1;
            set_min(i, j, cost);
        }
    }
}

int main(void) {
    cin >> T;
    while (T--) {
        cin >> a >> b;
        N = a.length(); M = b.length();
        a = " " + a; b = " " + b;
        dist.assign(N + 1, vi());
        for (int i = 0; i <= N; i++) dist[i].assign(M + 1, 0);
        levenshtei();
        cout << dist[N][M] << endl;
        dist.clear();
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define FOR(i,n) for (int i = 0; i < n; i++)
#define REP(i,n) for (int i = 1; i <= n; i++)
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef queue<ii> qii;
int T, N, M;
char grid[200][200];
int sol[200][200];
int positionX[] = {-1, 0, 1, 0};
int positionY[] = {0,-1, 0, 1};
vii whites;
qii children;

void bfs() {
    while (! children.empty()) {
        ii x = children.front();
        children.pop();
        for (int i = 0; i < 4; i++) {
            int newx = x.first + positionX[i], newy = x.second + positionY[i];
            if (newx >= 0 && newx < N && newy >= 0 && newy < M) {
                if (sol[x.first][x.second] + 1 < sol[newx][newy]) {
                    sol[newx][newy] = sol[x.first][x.second] + 1;
                    children.push(ii(newx, newy));
                }
            }
        }
    }
}
int main(void) {
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d", &N, &M);
        FOR(i, N) scanf("%s", grid[i]); 
        memset(sol, 50000, sizeof(sol));
        FOR(i, N) {
            FOR(j, M) {  
                if (grid[i][j] == '1') {
                    sol[i][j] = 0;
                    whites.push_back(ii(i,j));
                }
            }
        }
        FOR(i, whites.size()) {
            children.push(whites[i]);
            bfs();
        }
        FOR(i, N) {
            printf("%d", sol[i][0]);
            REP(j, M-1) {
                printf(" %d", sol[i][j]);
            }
            printf("\n");
        }
        whites.clear();
    }

    return 0;
}

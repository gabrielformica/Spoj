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
#include <cmath>

#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)

using namespace std;

int G, B;
int main() {
    while (scanf("%d %d", &G, &B), G != -1 && B != -1) {
        if (G == 0 && B == 0) {
            printf("0\n");
        } else if (G == B) {
            printf("1\n");
        } else {
            int imax = max(G, B), imin = min(G, B) + 1;
            int res = imax / imin;
            res += (imax % imin != 0) ? 1 : 0;
            printf("%d\n", res);
        }
    }
    return 0;
}

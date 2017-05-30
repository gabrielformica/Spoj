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

#define ri(X) scanf("%d",&X)
#define rii(X,Y) scanf("%d %d",&X,&Y)
#define rf(X) scanf("%lf",&X)
#define rff(X,Y) scanf("%lf %lf",&X,&Y)
#define mp(X,Y) make_pair(X,Y)
#define pii pair<int,int>
#define FOR(i,j) for(int i=0;i<j;i++)
#define FORC(i,j,c) for(int i=0;i<j;i+=c)

using namespace std;

int T, N, man[1005], woman[1005];
int main() {
    ri(T); 
    FOR(i, T) {
        ri(N);
        FOR(j, N) ri(woman[j]);
        FOR(j, N) ri(man[j]);
        sort(man, man + N);
        sort(woman, woman + N);
        int total = 0;
        FOR(i, N) {
            total += woman[i] * man[i];
        }
        printf("%d\n", total);
    }
    return 0;
}

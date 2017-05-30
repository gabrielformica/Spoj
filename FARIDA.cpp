#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAX 10000
using namespace std;
typedef long long int lli;

lli coins[MAX + 5], best[MAX + 5];
int T, m;

lli get_best(int i) {
    if (i >= m) return 0;
    if (best[i] != -1) return best[i];
    return best[i] = max(get_best(i + 2) + coins[i], get_best(i + 1));
}

int main(void) {
    scanf("%d", &T);
    for (int i = 1; i <= T; i++) {
        scanf("%d", &m); 
        for (int k = 0; k < m; k++) {
            scanf("%d", &coins[k]);
        }
        memset(best, -1, sizeof(best));
        lli x = get_best(0);
        cout << "Case " << i << ": " << x << endl;
    }
    return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define MAX 16
using namespace std;

int n, worst_value, memo[MAX + 5][ (1 << MAX) + 5]; 
int valid[MAX + 5], baby[MAX + 5];

int manhattan(int a, int b) { return abs(a - b) + abs(baby[a] - valid[b]); }

/**
  * gets the minimun number of moves required
  * @param row: the i-th row 
  * @param mask: bitmask of the occupied final position
  * @return the minimun number of moves required 
  */
int get_minimum(int row, int mask) {
    if ((row == n) && (mask == (1 << n) - 1)) {
        return 0;
    }
    if (memo[row][mask] != -1) return memo[row][mask];

    int hello = worst_value; 
    for (int m = 0; m < n; m++) {
        if (! ( mask & (1 << m) )) {
            hello = min(hello, manhattan(row, m) + get_minimum(row + 1, mask | (1 << m)));
        }
    }

    return memo[row][mask] = hello;
}

int main(void) {
    while (scanf("%d", &n), n != 0) {
        memset(memo, -1, sizeof(memo));
        worst_value = (1 << n) + 5;
        //reading baby's moves
        for (int i = 0; i < n; i++) scanf("%d", &baby[i]);

        //reading valid solution
        for (int i = 0; i < n; i++) scanf("%d", &valid[i]);

        //decrementing because of indices
        for (int i = 0; i < n; i++) {
            baby[i]--;
            valid[i]--;
        }
        int imin = get_minimum(0, 0);
        printf("%d\n", imin);
    }
    return 0;
}

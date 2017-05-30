#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX 1000000 
#define MIN 0
using namespace std;

int N, sequence[200 + 5], memo[205][205][205];

/**
  * Gets the maximun number of painted elements
  * @param i: i-th element
  * @param desc: possition of the best element in the descending sequence
  * @param asc: possition of the best element in the ascending sequence
  */
int get_max(int i, int desc, int asc) {
    if (i == N) return 0;
    if (memo[i][desc][asc] != -1) return memo[i][desc][asc];
    int a = -1 , b = -1 , c = -1;
    //white painting
    if (sequence[desc] > sequence[i]) {
        a = 1 + get_max(i + 1, i, asc);
    }
    //black painting
    if (sequence[asc] < sequence[i]) {
        b = 1 + get_max(i + 1, desc, i);
    }
    c = get_max(i + 1, desc, asc);   //no painting at all
    if (a == -1) return memo[i][desc][asc] = max(b, c);
    if (b == -1) return memo[i][desc][asc] = max(a, c);
    return memo[i][desc][asc] = max(a, max(b, c));
}

int main(void) {
    while (scanf("%d", &N), N != -1) { 
        memset(memo, -1, sizeof(memo));
        int counter = 0;
        for (int i = 0; i < N; i++) 
            scanf("%d", &sequence[i]);
        sequence[N] = MAX + 5;
        sequence[N+1] = MIN;

        int x = get_max(0, N, N+1); 
        printf("%d\n", N - x);  //print total - maximun painted elements
    }
    return 0;
}

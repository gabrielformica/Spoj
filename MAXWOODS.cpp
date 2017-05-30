#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX 200
using namespace std;

int row, column; 
int best[MAX + 5]; //memoization array
char line[MAX + 5]; 

int main(void) {
    int test;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &row, &column);
        memset(best, 0, sizeof(best));
        scanf("%s", line);
        bool possible = false;
        //Base case
        if (line[0] != '#') possible = true;
        if (line[0] == 'T') best[0] = 1;
        int imax = best[0];
        for (int i = 1; i < column; i++) {
            if ( best[i - 1] == -1  || line[i] == '#' )
                best[i] = -1;
            else {
                int T = line[i] == 'T';
                best[i] = T + best[i - 1]; 
            }
            imax = max(imax, best[i]);
        }
        int even = 0;  //if agent is facing right (even = 1)
        for (int i = 1; i < row; i++) {
            scanf("%s", line);
            int init = (even ? 0 : column - 1);
            int rest = (even ? 1 : -1);
            for (int j = init; j < column && j >= 0; j = j + rest) {
               if (line[j] == '#') {
                    best[j] = -1;
                    continue;
               }
               int T = line[j] == 'T';
               if (best[j - rest] == -1 && best[j] == -1)
                   best[j] = -1;
               else if (best[j] == -1 && j == column - 1 && !even) 
                   best[j] = -1;
               else if (best[j] == -1 && j == 0 && even) 
                   best[j] = -1;
               else
                   best[j] = max( best[ j - rest ] + T, best[j] + T); 
            
               imax = max(imax, best[j]);
            }
            even = ! even;
        }

        if (! possible) printf("0\n");
        else printf("%d\n", imax); 
    } 
    return 0;
}

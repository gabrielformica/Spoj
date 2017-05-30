#include <stdio.h>
#include <stdlib.h>
#define MAX 499995000

typedef struct t t;
struct t {
	int p;
	int w;
};

int minval();
int minv[10000];

int main() {
	
	int i, amountc, cases, pig, pige, pigf;
	scanf("%d",&cases);
	for (i = 0; i < cases; i++) {
		scanf("%d %d",&pige,&pigf);
		pig = pigf - pige;
		int g = 0;
		for (; g <= pig; g++)
			minv[g] = -1;
		scanf("%d",&amountc);		
		t coins[amountc];
		int j = 0;
		for(; j < amountc; j++) {
			int p,w;
			scanf("%d %d",&p,&w);
			coins[j].p = p;
			coins[j].w = w;
		}
		minv[pig] = minval(pig,coins,amountc);
		if (minv[pig] < MAX) {
			printf("The minimum amount of money in the piggy-bank is %d.\n",minv[pig]);
		}
		else {
			printf("This is impossible.\n");
		}
	}	
	return 0;
}

int minval(int w, t coins[], int amountc) {
	//caso base
	if (minv[w] != -1) {
		return minv[w];
	}
	if (w == 0) {
		minv[0] = 0;
		return 0;
	}

	int y = MAX;
	int i;
	for (i = 0; i < amountc; i++) {
		if (w >= coins[i].w) {
			int z = coins[i].p + minval(w - coins[i].w,coins,amountc);	
			if (z < y) {
				y = z;
			}
		}
	}
	minv[w] = y;
	return y;
}

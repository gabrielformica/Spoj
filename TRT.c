#include <stdio.h>
#include <stdlib.h>




int **arr;
int main() {
	int x, i, j, age;
	scanf("%d",&x);
	arr = malloc((x+1)*sizeof(int *));
	for (i = 0; i <= x ; i++) {
		arr[i] = malloc((x+1)*sizeof(int));
	}

	for (i = 0; i <= x; i++) {
		for (j = 0; j <= x; j++) {
			arr[i][j] = -1;
		}
	}	
	int *treats = malloc(x*sizeof(int));
	int y;
	for (i = 0; i < x; i++) {
		int y;
		scanf("%d",&treats[i]);	
	}	
	int max = maxv(treats,0,x-1,1);
	printf("%d\n",max);
	return 0;
}

int maxv(int *treats, int i, int j, int age) {
	if (i > j) {
		return 0;
	}	
	if (arr[i][j] != -1) {
		return arr[i][j];
	}
	int x = maxv(treats,i+1,j,age+1) + treats[i]*age;
	int z = maxv(treats,i,j-1,age+1) + treats[j]*age;
	if (x > z) {
		arr[i][j] = x;
		return x;
	}
	arr[i][j] = z;
	return z;
}

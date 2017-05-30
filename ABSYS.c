#include <stdlib.h>
#include <stdio.h>

int main(int arg, char *argv[]) {
	char str[3][100];
	char str1;
	char str2;
	int i;
	scanf("%d",&i);
	while (i > 0) {
		scanf("%s %c %s %c %s",str[0],&str1,str[1],&str2,str[2]);
		int j,q;
		int p = 0;
		for (q = 0; (!p); q++) {
			for (j = 0; str[q][j] != '\0'; j++) {
				if (str[q][j] == 'm') {
					p++;	
				}
			}
			if (p) 
				break;
		}
		int x,y,z;
		if (q == 0) {
			y = atoi(str[1]);		
			z = atoi(str[2]);
			x = z - y;
		}
		else if (q == 1) {
			x = atoi(str[0]);
			z = atoi(str[2]);
			y = z - x;
		}
		else {
			x = atoi(str[0]);
			y = atoi(str[1]);		
			z = x + y;
		}
		printf("%d + %d = %d\n",x,y,z);
		i--;
	}
}

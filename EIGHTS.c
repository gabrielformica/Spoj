#include <stdlib.h>
#include <stdio.h>

int main(){
	long long x;
	scanf("%lld",&x);
	while (x > 0) {
		long long y;
		scanf("%lld",&y);
		y = 192 + (y-1)*250;
		printf("%lld\n",y);
		x--;
	}
}

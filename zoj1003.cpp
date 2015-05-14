#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
int win0 = 0, win1 = 0;
void possible(int big, int small, int n)
{
	if (win0 == 1)
		return;
	if (small == 1 && big == 1){
		win0 = 1; return;
	}
	if (small == 1)
		win1 = 1;

	if (n == 1){
		return;
	}
	
	for (int i = n; i > 1; i--){
		
		if (small%i == 0)
			possible(big, small / i, i - 1);
		if (big%i == 0)
			possible(big / i, small, i - 1);
	}
	
}

int main(){
	int s1, s2;
	int big, small;
	while (scanf("%d%d", &s1, &s2) != EOF){
		win0 = 0,win1=0;
		if (s1 > s2){
			big = s1;
			small = s2;
		}
		else{
			big = s2;
			small = s1;
		}
		possible(big, small, 100);
		if (win0==1 || win1==0)
			printf("%d\n", big);
		else
			printf("%d\n", small);
	}
	return 0;
}

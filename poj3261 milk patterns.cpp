#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)

#define MAX 1000001
int sa[MAX], rank[MAX], height[MAX], trank[MAX],tsa[MAX],sum[MAX],s[MAX];

void sorting(int j, int n,int m){

	int th = 1;
	for (int i = n + 1 - j; i <= n; i++)tsa[th++] = i;
	for (int i = 1; i <= n; i++){
		if (sa[i] > j)
			tsa[th++] = sa[i] - j;
	}
	memset(sum, 0, sizeof(sum));
	for (int i = 1; i <= n; i++)sum[rank[i]]++;
	for (int i = 1; i <= m; i++)sum[i] += sum[i - 1];
	for (int i = n; i > 0; i--){
		sa[sum[rank[tsa[i]]]--] = tsa[i];
	}
	int p = 1;
	trank[sa[1]] = 1;
	for (int i = 2; i <= n; i++){
		if ((rank[sa[i]] != rank[sa[i - 1]]) || (rank[sa[i] + j] != rank[sa[i - 1] + j]))p++;
		trank[sa[i]] = p;
	}
	for (int i = 1; i <= n; i++){
		rank[i] = trank[i];
	}
}
void get_sa(int n,int m){
	int i,j;
	memset(sum, 0, sizeof(sum));
	for (i = 1; i <= n; i++)sum[s[i]]++;
	for (i = 1; i <= m; i++)sum[i] += sum[i - 1];
	for (i = n; i > 0; i--){
		sa[sum[s[i]]--] = i;
	}
	int p = 0;
	for (i = 1; i <= n; i++){
		if (s[sa[i - 1]] != s[sa[i]])p++;
		rank[sa[i]] = p;	
	}
	for (j = 1; j <= n; j *= 2){
		sorting(j,n,m);
	}
}
void get_height(int n){
	for (int i = 1, j = 0; i <=n; i++)
	{
		if (rank[i] == 1) continue;
		for (; s[i + j] == s[sa[rank[i] - 1] + j];) j++;
		height[rank[i]] = j;
		if (j>0) j--;
	}
}

int ismatch(int len, int k,int n){
	int cnt = 0;
	for (int i = 2; i <= n; i++){
		
		if (height[i] >= len){
			cnt++;
			if (cnt >= k)return 1;
		}
		else cnt = 0;
	}
	return 0;
}
int main(){
	int i, n, k,m;
	while (scanf("%d", &n) != EOF){
		scanf("%d", &k);
		m = -1;
		for (i = 1; i <= n; i++){
			scanf("%d", &s[i]);
			if (m < s[i])m = s[i]; 
		}
		if (m < n)m = n;
		get_sa(n,m);
		get_height(n);
		int ans = 0;
		int l = 1, r = n;
		while (l <= r){
			int mid = (l + r) / 2;
			if (ismatch(mid, k - 1, n)){
				ans = mid;
				l = mid+1 ;
			}
			else{
				r = mid-1;
			}
		}
		printf("%d\n", ans);
	}
}
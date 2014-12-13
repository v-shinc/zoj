#include<algorithm>
#include<iostream>
#include<string>
#include<stdio.h>
#include<queue>
#pragma warning(disable:4996)
using namespace std;
const int MAX = 50;
const int INF = 10000000;
const int s = 0, t = 49;
int m1[MAX][MAX],m2[MAX][MAX];
int a[MAX], b[MAX];


int vis[MAX],path[MAX],bestPath[MAX],bestDist,fee,len;
int dij[MAX];
void DFS(int cur,int dis,int cos,int l){
	
	if (cur == t){
		if (dis < bestDist){
			for (int i = 0; i < l; i++)
				bestPath[i] = path[i];
			bestDist = dis;
			fee = cos;
			len = l;
			
		}
		return;
	}
	for (int i = 0; i < MAX; i++){
		if (vis[i])continue;
		if (m1[cur][i] == 9999)
			continue;
		if (dis+m1[cur][i] + dij[i] > bestDist || cos + m2[cur][i]+ b[i] > 1500)
			continue;
		path[l] = i;
		vis[i] = 1;
		DFS(i, dis + m1[cur][i], cos + m2[cur][i], l + 1);
		vis[i] = 0;
	}
}

void dijkstra(int *d,int m[MAX][MAX],int t){
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < MAX; i++)
		d[i] = INF;
	d[t] = 0;
	for (int i = 0; i < MAX; i++){
		int pos = -1;
		for (int j = 0; j < MAX; j++){
			if (!vis[j] && (pos == -1 || d[j] < d[pos]))
				pos = j;
		}
		vis[pos] = 1;
		for (int j = 0; j < MAX; j++){
			if (!vis[j] && (d[j] > d[pos] + m[j][pos])){
				d[j] = d[pos] + m[j][pos];
			}
		}
	}
}
int main(){
	char * distFile = "m1.txt";
	char * costFile = "m2.txt";
	FILE *dist = fopen(distFile,"r");
	FILE *cost = fopen(costFile, "r");
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++){
			fscanf(dist, "%d", &m1[i][j]);
		}
			
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			fscanf(cost, "%d", &m2[i][j]);
	//floyd();
	bestDist = INF;
	vis[0] = 1;
	memset(vis, 0, sizeof(vis));
	dijkstra(a, m1, t);
	memset(vis, 0, sizeof(vis));
	dijkstra(b, m2, t);
	memset(vis, 0, sizeof(vis));
	DFS(0, 0, 0, 0);
	for (int i = 0; i < len; i++)
		printf("%d ", bestPath[i]);
	printf("\n%d %d\n", bestDist, fee);
		
	return 0;

}
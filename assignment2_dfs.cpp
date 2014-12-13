#include<algorithm>
#include<iostream>
#include<string>
#include<stdio.h>
#include<queue>
#pragma warning(disable:4996)
using namespace std;
const int MAX = 50;//顶点数
const int INF = 10000000;
const int s = 0, t = 49;
int m1[MAX][MAX]; //城市间长度矩阵
int m2[MAX][MAX]; //养路费用矩阵
int a[MAX];       //到终点城市最短距离（不考虑养路费）
int b[MAX];       //到终点城市最小养路费


int vis[MAX];
int path[MAX];
int bestPath[MAX];//最有路径
int bestDist;     //起点到终点最短距离（考虑养路费）上界
int fee, len;
void DFS(int cur, int dis, int cos, int l){

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
		//已经过的距离+剩余距离下界>距离上界 或 已花费的养路费 + 养路费下界 > 养路费上界 则剪枝
		if (dis + m1[cur][i] + a[i] > bestDist || cos + m2[cur][i] + b[i] > 1500)
			continue;
		path[l] = i;
		vis[i] = 1;
		DFS(i, dis + m1[cur][i], cos + m2[cur][i], l + 1);
		vis[i] = 0;
	}
}

void dijkstra(int *d, int m[MAX][MAX], int t){
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
	FILE *dist = fopen(distFile, "r");
	FILE *cost = fopen(costFile, "r");
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			fscanf(dist, "%d", &m1[i][j]);

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			fscanf(cost, "%d", &m2[i][j]);

	bestDist = INF;
	vis[0] = 1;
	path[0] = 0;
	dijkstra(a, m1, t);
	dijkstra(b, m2, t);
	memset(vis, 0, sizeof(vis));
	DFS(0, 0, 0, 1);
	for (int i = 0; i < len; i++)
		printf("%d ", bestPath[i]);
	printf("\n%d %d\n", bestDist, fee);

	return 0;

}
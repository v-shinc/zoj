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
int m1[MAX][MAX], m2[MAX][MAX];
int a[MAX], b[MAX];

struct BNode{
	BNode * fa;
	int pos;
	BNode(){}
	BNode(BNode* f, int p){
		fa = f, pos = p;
	}
}tree[1000];
struct HeapNode{
	BNode *bnode;
	int pos;
	int ldist;
	int cost;
	int dist;
	HeapNode(){}

	HeapNode(int p, int ld, int c, int d){
		pos = p;
		ldist = ld;
		cost = c;
		dist = d;

	}
	friend bool operator< (HeapNode n1, HeapNode n2){
		return n1.ldist > n2.ldist;
	}

};
int vis[MAX];
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

int bestDist[MAX];
int bestCost[MAX];
int main(){
	char * distFile = "m1.txt";
	char * costFile = "m2.txt";
	FILE *dist = fopen(distFile, "r");
	FILE *cost = fopen(costFile, "r");
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++){
		fscanf(dist, "%d", &m1[i][j]);
		}

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			fscanf(cost, "%d", &m2[i][j]);
	dijkstra(a, m1, t);
	dijkstra(b, m2, t);
	priority_queue<HeapNode> pq = priority_queue<HeapNode>();
	HeapNode root = HeapNode(s, a[s], 0, 0);
	tree[0] = BNode(NULL, 0);
	root.bnode = &tree[0];
	pq.push(root);

	for (int i = 0; i < MAX; i++)bestDist[i] = INF, bestCost[i] = INF;
	HeapNode bestNode;
	int k = 1;
	while (!pq.empty()){
		HeapNode hn = pq.top();
		pq.pop();
		if (hn.pos == t){
			bestNode = hn;
			break;
		}
		int cur = hn.pos;
		for (int i = 0; i < MAX; i++){
			if (m1[cur][i] == 9999)
				continue;
			if (hn.cost + m2[cur][i] + b[i] > 1500)
				continue;
			int dis = hn.dist + m1[cur][i];
			int cos = hn.cost + m2[cur][i];
			if (dis < bestDist[i] || cos < bestCost[i]){
				int ldist = dis + a[i];
				HeapNode node = HeapNode(i, ldist, cos, dis);
				tree[k] = BNode(hn.bnode, i);
				node.bnode = &tree[k];
				k++;

				pq.push(node);
			}
			if (dis <= bestDist[i] && cos <= bestCost[i]){
				bestDist[i] = dis, bestCost[i] = cos;
			}



		}
	}
	BNode *cur = bestNode.bnode;
	while (cur != NULL){
		printf("%d ", cur->pos);
		cur = cur->fa;
	}
	printf("%d\n", bestDist[t]);
	return 0;

}
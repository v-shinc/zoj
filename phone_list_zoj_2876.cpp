

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)


const int MAX = 10;
typedef struct Node{
	int isword;
	struct Node* children[10];
}Node, *Trie;
Node* createNode(){
	Node *p = (Node*)malloc(sizeof(Node));
	p->isword = 0;
	memset(p->children, 0, sizeof(p->children)); 
		return p;
}
int insert(Node* root, char *word){
	int flag = 0;
	int len = strlen(word), i;

	Node *cur = root;
	for (i = 0; i<len; i++){
		int c = word[i] - '0';
		if (cur->children[c]){
			cur = cur->children[c];
		}
		else{
			flag = 1;
			if (cur->isword){
				return 0;
			}
			cur->children[c] = createNode();
			cur = cur->children[c];
		}
	}
	cur->isword = 1;
	return flag;
}
void deleteTrie(Trie root){
	int i;
	for (i = 0; i<MAX; i++){
		if (root->children[i])
			deleteTrie(root->children[i]);
	}
	free(root);
}
int main(int argc, const char * argv[]) {
	int cas, n, i, res;
	scanf("%d", &cas);
	char str[100]; 
	while (cas){
		res = 1;
		Trie tree = createNode();
		scanf("%d", &n);
		for (i = 0; i<n; i++){
			scanf("%s", str);
			if (!res)
				continue;
			res &= insert(tree, str);
		}
		if (res)
			printf("YES\n");
		else
			printf("NO\n");
		deleteTrie(tree);
		cas--;
	}


	return 0;
}

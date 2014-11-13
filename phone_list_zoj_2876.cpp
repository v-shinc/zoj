/*
标准tire树，一边插入单词一边检查合法性。
假设当前插入word
1)判断树中是否有单词时word的前缀
比如树中已有“911”、“97625999”，当前插入“91125426”。当walk到第二个‘1’结点时，发现该结点的isword=1，则表示树中存在前缀。
2）假设树中有“91125426”，当前插入“911”，若整个插入过程没有创建任何新结点（flag=0）,则当前结点是树中某个单词的前缀。
*/

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

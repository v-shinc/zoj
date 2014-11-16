/*题意：给定一本英文-火星文字典（字典中单词小写），把火星文
翻译成英文，没有出现在字典中的单词不翻译，标点符号原样输出*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable:4996)

typedef struct Node{
	struct Node *children[26];
	char word[11];
}Node, *Trie;

Node *createNode(){
	Node *p = (Node*)malloc(sizeof(Node));
	memset(p->children, 0, sizeof(p->children));
	//memset(p->word, 0, sizeof(p->word));
	strcpy(p->word, " ");
	return p;
}
void insert(Trie tree, char *english, char *martian){
	Node *cur = tree;
	int i, len = strlen(martian);
	for (i = 0; i < len; i++){
		int c = martian[i] - 'a';
		if (!cur->children[c]){
			cur->children[c] = createNode();
		}
		cur = cur->children[c];
	}
	strcpy(cur->word, english);
	cur->word[strlen(english)] = '\0';
}
char *find(Trie tree, char *martian){
	Node *cur = tree;
	int i, len = strlen(martian);
	for (i = 0; i < len; i++){
		int c = martian[i] - 'a';
		if (!cur->children[c]){
			return NULL;
		}
		cur = cur->children[c];
	}
	if (strcmp(cur->word, " ") == 0)
		return NULL;
	return cur->word;
}
void deleteTrie(Trie root){
	int i;
	for (i = 0; i < 26; i++){
		if (root->children[i])
			deleteTrie(root->children[i]);
	}
	free(root);
}
int main(){
	char str[3000];
	char mar[15], eng[15];
	char word[3000];
	int len, i;
	char ch;

	scanf("%s", str);
	getchar();
	Trie tree = createNode();
	while (scanf("%s", eng) && strcmp(eng, "END")){
		scanf("%s", mar);
		//eng = strtok(str, " ");
		//mar = strtok(NULL, " ");
		insert(tree, eng, mar);
	}
	scanf("%s", str);
	getchar();
	while (gets(str) && strcmp(str, "END")){

		len = strlen(str);
		str[len] = ' ';
		len++;
		int idx = 0;
		for (i = 0; i < len; i++){
			ch = str[i];
			if (ch >= 'a'&&ch <= 'z'){
				word[idx] = ch;
				idx++;
			}
			else{
				word[idx] = '\0';
				char *english = find(tree, word);
				if (english == NULL){
					printf("%s", word);
				}
				else{
					printf("%s", english);
				}
				if (i != len - 1)
					printf("%c", ch);
				memset(word, 0, sizeof(word));
				idx = 0;
			}
		}
		printf("\n");
	}
	deleteTrie(tree);
}
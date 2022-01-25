#include "include/includes.h"
#include "include/print.h"


int CountKeyNum(BTree &tree){
	if (tree == NULL) return 0;
	int childTotal = 0;
	for (int i = 0; i <= tree->count; i++) {
		childTotal += CountKeyNum(tree->ptr[i]);
	}
	return tree->count + childTotal;
}


void TraverseBTree(BTree &tree){
	int layer = 0;
	int* isEnd = (int*)malloc(sizeof(int) * (CountKeyNum(tree) + 10));
	printf("\n");
	PrintBTree(tree, isEnd, layer);
}


void PrintBTree(BTree &tree, int isEnd[], int layer) {
	if (tree == NULL) return;
	printf("©·\n");
	for (int i = 0; i <= tree->count; i++) {
		if (tree->ptr[i] != NULL) {
			printBranch(isEnd, layer);
			printf("©Ç©¥©¥©¥©¥©¥©¥");
			isEnd[layer++] = (i == tree->count);
			PrintBTree(tree->ptr[i], isEnd, layer);
			layer--;
		}
		if (i != tree->count) {
			printBranch(isEnd, layer);
			printf("©Ç©¥ %d\n", tree->key[i+1]);
		}
	}
}


void printBranch(int isEnd[], int layer) {
	for (int i = 0; i < layer; i++) {
		if (isEnd[i]) printf(" ");
		else printf("©§");
		printf("      ");
	}
}

#pragma once
#include "includes.h"

int CountKeyNum(BTree &tree);
void TraverseBTree(BTree &tree);
void PrintBTree(BTree &tree, int isEnd[], int layer);
void printBranch(int isEnd[], int layer);
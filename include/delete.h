#pragma once
#include "includes.h"

Status DeleteBTree(BTree &T, KeyType key);
void Successor(BTree &note, int &index);
Status RemoveRecord(BTree& note, int i);
Status InsertRecord(BTree& node, KeyType key,int i, Record rcd);
void RestoreBTree(BTree& node, int pi);
void CombineBTNode(BTree& left, BTree& right);
void DeleteRoot(BTree& root);
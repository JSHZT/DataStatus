#pragma once
#include "includes.h"

int InsertBTree(BTree &T, KeyType k, Record rcd);
void SplitNote(BTree &note, BTree &newnote);
void Insert(BTree &note, KeyType k, int index, BTree newchild, Record rcd);
void NewRoot(BTree &T, BTree l_note, BTree r_note, KeyType k, Record rcd);
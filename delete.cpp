#include "include/includes.h"
#include "include/search.h"
#include "include/delete.h"
#include "include/insert.h"

Status DeleteBTree(BTree &T, KeyType key){
	Result result;
    SearchBTree(T, key, result);
	if (result.has_found == 0) return ERROR;
	if (result.btnote->ptr[0] != NULL) Successor(result.btnote, result.index);
	key = result.btnote->key[result.index];
	RemoveRecord(result.btnote, result.index);
	int index_s = Search(result.btnote->parent, key) - 1;
	if (result.btnote->parent != NULL && result.btnote->count < MIN_KEY_NUM)
        RestoreBTree(result.btnote, index_s);
	return OK;
}

void Successor(BTree &note, int &index){
    if(note == NULL) return;
	if(note->ptr[index - 1] == NULL) return;
	BTree search = note->ptr[index - 1];
	while(search->ptr[search->count] != NULL)
        search = search->ptr[search->count];
	note->key[index] = search->key[search->count];
	note->rcd_ptr[index] = search->rcd_ptr[search->count];
	note = search;
	index = search->count;
}

Status RemoveRecord(BTree& note, int i){
	if (note == NULL) return ERROR;
	for (; i < note->count; i++) {
		note->key[i] = note->key[i + 1];
		note->rcd_ptr[i] = note->rcd_ptr[i + 1];
        //note->ptr[i] = note->ptr[i + 1];
	}
	note->count--;
	note->rcd_ptr[i] = NULL;
    //note->ptr[i] = NULL;
	return OK;
}

Status InsertRecord(BTree& node, KeyType key,int i, Record rcd) {
	if (node == NULL) return ERROR;
	for (int j = node->count; j >= i; j--) {
		node->key[j + 1] = node->key[j];
		node->rcd_ptr[j + 1] = node->rcd_ptr[j];
	}
	node->key[i] = key;
	node->rcd_ptr[i] = rcd;
	node->count++;
    return OK;
}


void RestoreBTree(BTree& node, int pi) {
	BTree parent, brother;
	parent = node->parent;
	KeyType key;
	if (pi > 0 && (brother = parent->ptr[pi - 1])->count > MIN_KEY_NUM) {
		Insert(node, parent->key[pi], 1, node->ptr[0], parent->rcd_ptr[pi]);
		node->ptr[0] = brother->ptr[brother->count];
		if (brother->ptr[brother->count] != NULL) brother->ptr[brother->count]->parent = node;
		RemoveRecord(parent, pi);
		InsertRecord(parent, brother->key[brother->count], pi, brother->rcd_ptr[brother->count]);
		RemoveRecord(brother, brother->count);
	}
	else if (pi < parent->count && (brother = parent->ptr[pi + 1])->count > MIN_KEY_NUM) {
		Insert(node, parent->key[pi+1], node->count + 1, brother->ptr[0], parent->rcd_ptr[pi + 1]);
		RemoveRecord(parent, pi + 1);
		InsertRecord(parent, brother->key[1], pi + 1, brother->rcd_ptr[1]);
		RemoveRecord(brother, 1);
		for (int i=0; i <= brother->count; i++) brother->ptr[i] = brother->ptr[i + 1];
	}
	else if (pi > 0) {
		brother = parent->ptr[pi - 1];
		Insert(node, parent->key[pi], 1, node->ptr[0], parent->rcd_ptr[pi]);
		RemoveRecord(parent, pi);
		CombineBTNode(brother, node);
		node = brother;
		for (int i = pi; i <= parent->count; i++) parent->ptr[i] = parent->ptr[i + 1];

		if (parent->count < MIN_KEY_NUM) {
			if (parent->parent == NULL) DeleteRoot(parent);
			else RestoreBTree(parent, Search(parent->parent, node->key[1]) - 1);
		}
	}
	else {
		brother = parent->ptr[pi + 1];
		Insert(node, parent->key[pi+1],node->count + 1, brother->ptr[0], parent->rcd_ptr[pi + 1]);
		RemoveRecord(parent, pi + 1);
		CombineBTNode(node, brother);
		for (int i = pi + 1; i <= parent->count; i++) 
            parent->ptr[i] = parent->ptr[i + 1];
		if (parent->count < MIN_KEY_NUM) {
			if (parent->parent == NULL) DeleteRoot(parent);
			else RestoreBTree(parent, Search(parent->parent, node->key[node->count + 1]) - 1);
		}
	}
}

void CombineBTNode(BTree& left, BTree& right) {
	if (left == NULL) return;

	for (int i = 1; i <= right->count; i++) {
		Insert(left, right->key[i], left->count + 1, right->ptr[i], right->rcd_ptr[i]);
	}

	free(right);
    return;
}

void DeleteRoot(BTree& root) {
	BTree ptr = root->ptr[0];
	root->ptr[0] = ptr->ptr[0];
	if (ptr->ptr[0] != NULL) ptr->ptr[0]->parent = root;
	for (int i = 1; i <= ptr->count; i++) Insert(root, ptr->key[i], i, ptr->ptr[i], ptr->rcd_ptr[i]);
    return;
}

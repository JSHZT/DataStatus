#include "include/includes.h"
#include "include/search.h"
#include "include/insert.h"

int InsertBTree(BTree &T, KeyType k, Record rcd){
    Result result;
    SearchBTree(T, k, result);
    if(result.has_found)return ERROR;
    Insert(result.btnote, k, result.index, NULL, rcd);
    BTree newnode;
    while (result.btnote->count >= MAX_KEY_NUM  ){
		SplitNote(result.btnote, newnode);
		if (result.btnote->parent == NULL){
            NewRoot(T, result.btnote, newnode, result.btnote->key[CUT_INDEX], result.btnote->rcd_ptr[CUT_INDEX]);
            result.btnote->key[CUT_INDEX] = -1;
            result.btnote->rcd_ptr[CUT_INDEX] = NULL;
        }
		else {
			int i = Search(result.btnote->parent, result.btnote->key[CUT_INDEX]);
			Insert(result.btnote->parent, result.btnote->key[CUT_INDEX], i, newnode, result.btnote->rcd_ptr[CUT_INDEX]);
		}
        result.btnote = result.btnote->parent;
        if(result.btnote==NULL) break;
    }
    return OK;
}

void SplitNote(BTree &note, BTree &newnote){
    int i, j, num = note->count;
    newnote = (BTNote*)malloc(sizeof(BTNote));
    InitBTNote(newnote);
    newnote->ptr[0] = note->ptr[CUT_INDEX];
    for(i = CUT_INDEX + 1, j = 1; i<=num;i++,j++){
        newnote->key[j] = note->key[i];
        newnote->ptr[j] = note->ptr[i];
        newnote->rcd_ptr[j] = note->rcd_ptr[i];
        note->key[i] = -1;
        note->ptr[i] = NULL;
        note->rcd_ptr[i] = NULL;
    }
    newnote->count = num-CUT_INDEX;
    newnote->parent = note->parent;
    for(i=0;i<=num-CUT_INDEX;i++)
        if(newnote->ptr[i]!=NULL) newnote->ptr[i]->parent = newnote;
    note->count = CUT_INDEX - 1;
    return;
}

void Insert(BTree &note, KeyType k, int index, BTree newchild, Record rcd){
    int i;
    for(i = note->count; i>=index; i--){
        note->key[i+1] = note->key[i];
        note->ptr[i+1] = note->ptr[i];
        note->rcd_ptr[i+1] = note->rcd_ptr[i];
    }
    note->key[index] = k;
    note->ptr[index] = newchild;
    note->rcd_ptr[index] = rcd;
    if(newchild!=NULL) newchild->parent = note;
    note->count++;
    return;
}

void NewRoot(BTree &T, BTree l_note, BTree r_note, KeyType k, Record rcd){
    T = (BTNote*)malloc(sizeof(BTNote));
    T->count = 1;
    T->ptr[0] = l_note;
    T->ptr[1] = r_note;
    T->key[1] = k;
    T->rcd_ptr[1] = rcd;
    if(l_note!=NULL) l_note->parent = T;
    if(r_note!=NULL) r_note->parent = T;
    T->parent = NULL;
}

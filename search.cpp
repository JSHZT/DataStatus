#include "include/includes.h"
#include "include/search.h"

void SearchBTree(BTree T, KeyType k, Result &r){
    int i = 0, found = 0;
    BTree ptemp1 = T, ptemp2 = NULL;
    while((ptemp1)!=NULL&&0==found){
        i = Search(ptemp1, k);
        if(i<=ptemp1->count && ptemp1->key[i]==k) found = 1;
        else{
            ptemp2 = ptemp1;
            ptemp1 = ptemp1->ptr[i-1];
        }
    }
    if(1 == found){
        r.has_found = 1;
        r.btnote = ptemp1;
        r.index = i;
    }else{
        r.has_found = 0;
        r.btnote = ptemp2;
        r.index = i;
    }
    return;
}

int Search(BTree p, KeyType k){
    int i=1;
    while(i <= p->count&&k>p->key[i]) i++;
    return i;
}
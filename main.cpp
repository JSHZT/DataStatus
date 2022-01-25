#include "include/includes.h"
#include "include/search.h"
#include "include/insert.h"
#include "include/print.h"
#include "include/delete.h"

int main(int argc, const char** argv) {
    BTree T;
    InitBTNote(T);
    record rcd[7];
    rcd[0].data = 20;
    rcd[1].data = 10;
    rcd[2].data = 30;
    rcd[3].data = 40;
    rcd[4].data = 25;
    rcd[5].data = 44;
    rcd[6].data = 59;
    
    KeyType k[7];
    for(int i = 0;i<7;i++) k[i] = i;
    for(int j = 0;j<7;j++)InsertBTree(T, k[j], &rcd[j]);
    TraverseBTree(T);
    DeleteBTree(T, 2);
    TraverseBTree(T);
    getchar();
    return 0;
}

void InitBTNote(BTree &note){
    note = (BTree)malloc(sizeof(BTNote));
    for(int i = 0;i<=m+1;i++){
        note->key[i] = -1;
        note->ptr[i] = NULL;
        note->rcd_ptr[i] = NULL;
    }
    note->count = 0;
    note->parent = NULL;
    return;
}
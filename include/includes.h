#pragma once
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define m 4
#define MAX_KEY_NUM m
#define MIN_KEY_NUM (m-1)/2 
#define CUT_INDEX (m+1)/2
#define KeyType int
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW 2
#define datatype int

typedef struct{
    datatype data;
}record, *Record;

typedef struct BTNote{
    int count;
    KeyType key[m+1];
    struct BTNote* parent;
    struct BTNote* ptr[m+1];
    Record rcd_ptr[m+1];
}BTNote, *BTree;

typedef struct{
    int has_found;
    int index;
    BTNote* btnote;
}Result, *pResult;

void InitBTNote(BTree &note);
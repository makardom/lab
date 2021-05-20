#pragma once
#define B
#include <stdio.h>

#ifdef B

typedef struct Info{
    char *str1;
    char *str2;
}Info;

typedef struct Item{
    //Info *info;
    int infooffset;
    int length;
    struct KeySpace1 **key1;
    struct KeySpace2 *key2;
    int ver2;
} Item;

typedef struct KeySpace1{
    char *key1;
    int keyoffset;
    int ver;
    struct Item *item;
    struct KeySpace1 *next;
} KeySpace1;

typedef struct Node2{
    int ver2;
    struct Item *item;
    struct Node2 *next;
} Node2;

typedef struct KeySpace2{
    unsigned int key2;
    struct Node2 *node;
    struct KeySpace2 *next;
} KeySpace2;

typedef struct Table{
    struct KeySpace1 *ks1;
    struct KeySpace2 **ks2;
    int csize1;
    FILE *keys;
    FILE *info;
}Table;

typedef struct FileKey{
    int keyoffset;
    int keylength;
    unsigned int key2;
    int infooffset;
    int onfolength;
} FileKey;

//Functions need to enter element in table
int EnterElement(Table *a, char *key1, unsigned int key2, int infooff, int infolength);
int CheckKeys(Table *a, char *key1, unsigned int key2);
void AddInSpace1(struct Item *item, struct Table *a, char *key1);
void AddInSpace2(Item *item, Table *a, unsigned int key2);

///////////////////////////////////////////////////////////////////////

void PrintTableConsole(Table *table);
//void PrintTable(Table *table, FILE *fp);

//////////////////////////////////////////////////////////////////////
//Functions work with both keyspace
int CheckVersion2(Table *a, unsigned int key);
int SearchElementByTwoKey(Table *a, char *key1, unsigned int key2);
int DeleteByTwoKeys(Table *a, char *key1, unsigned int key2);

//////////////////////////////////////////////////////////////////////
//Functions work with 1-st keyspace
void SearchSpace1Without(Table *a, char *key);
void SearchSpace1WithVer(Table *a, char *key, unsigned int ver);
int DeleteElementsBySpace1(Table *a, char *key);
int DeleteElementVerBySpace1(Table *a, char *key, unsigned int ver);

//////////////////////////////////////////////////////////////////////

void SearchSpace2Without(Table *a, unsigned int key);
void SearchSpace2WithVer(Table *a, unsigned int key, unsigned int ver);

///////////////////////////////////////////////////////////////////////

int DeleteElementsBySpace2(Table *a, unsigned int key);

//FILE *Resetfile(char *name);
//int CheckEmpty(KeySpace1 *ks1);
int D_TakeTable(Table **table, FILE **fp);
//Item *TakeItem(int offset, FILE *fp);
int OpenFile (FILE **fp, char *name);
int OpenFileToRecord(FILE **fp, char *name);
char *TakeKey1(FILE *fp, int offset, int length);
char * TakeInfo(FILE *fp,int offset, int length, char **inf1, char **inf2);
void SplitInfo(char *string, char **inf1, char **inf2, int length);
void RecordTable(FILE *fp, Table *a);
void PushInfoInFile(Table *a, char *info1, char *info2);

#endif

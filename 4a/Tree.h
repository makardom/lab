#pragma once
#include <stdio.h>
#include <time.h>

#define N 50

typedef struct Info{
    float num1;
    float num2;
    char *str;
}Info;

typedef struct Item{
    char *key;
    int ver;
    struct Item *right;
    struct Item *left;
    Info *info;
}Item;

typedef struct Tree{
    Item *node;
    int size;
}Tree;

void AddNodeInTree(Tree *a, Info *info, char *key);
void TreeInit(Tree **a);
int SearchElement(Tree *a, char *key, int ver);
void DeleteTree(Tree **a);
void DeleteNodes(Item *node);
void DeleteNode(Item *node);
int DeleteElement(Tree *a, char *key, int ver);
void AddInTree(Item *node, Item *add, char *key);
void PrintTreeTwo(Item *a);
void PrintBigger(Tree *a);
int LoadTree(FILE *fp, Tree *a);
void SaveInFile(FILE *fp, Item *a);
void D_Timing();
void Timing(double *add, double *del, double *ser, int n);
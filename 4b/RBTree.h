#pragma once

#include <stdio.h>

#define RED 1
#define BLACK 0

typedef struct Info{
    float num1;
    float num2;
    char *str;
}Info;

typedef struct Node{
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    char *key;
    struct Info *info;
    int color;
    int ver;
}Node;

typedef struct Tree{
    Node *node;
    int size;
}Tree;

void AddNodeInTree(Tree *a, Info *info, char *key, Node *Elist);
void SecondStepToAdd(Tree *a, Node *add, Node *Elist);
void TreeInit(Tree **a, Node *Elist);
void NodeInit(Node **elem, Node *Elist);
void AddInTree(Node *node, Node *add, char *key, Node *Elist, int ver);
void Left_Rotate(Tree *a, Node *x, Node *EList);
void Right_Rotate(Tree *a, Node *x, Node *EList);
int LoadTree(FILE *fp, Tree *a, Node *Elist);
void SaveInFile(FILE *fp, Node *a, Node *Elist);
int SearchElement(Tree *a, char *key, int ver, Node *Elist);
void DeleteNodes(Node *node, Node *Elist);
void DeleteTree(Tree **a, Node *Elist);
int DeleteElement(Tree *a, char *key, int ver, Node *Elist);
int DeleteNode (Tree *a, char *key, int ver, Node *Elist);
void Timing(double *add, double *del, double *ser, int n, Node *Elist);
void FixRightRed(Tree *a, Node *x, Node *Elist);
int Visualization(Node *node, Node *Elist, int k);

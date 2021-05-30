#pragma once
#include <stdio.h>

typedef struct Edge{
    struct Node *node;
    int cap; // пропускная способность
    struct Edge *next;
}Edge;

typedef struct Node{
    int name;
    int x;
    int y;
    struct Edge *edges;
} Node;

typedef struct Element{
    struct Node *node;
    struct Element *next;
}Element;

typedef struct Graph{
    struct Element *nodes;
    int kol;
} Graph;

typedef struct Tree{
    int name;
    struct Tree **branch;
    int kol;
}Tree;

void InitGraph(Graph **a);
void InitNode(Node *a);
int AddNodeInGraph(Graph *a, Node *add);
int AddEdgeInGraph(Graph *a, int name1, int name2);
int DeleteEdgeInGraph(Graph *a, int name1, int name2);
int DeleteNodeInGraph(Graph *a, int name);
int SearchInDeep(Graph *a, int name1, int name2);
int *Search_Shortest(Graph *a, int name1, int name2);
void GraphDelete(Graph *a);
int SaveInFile(FILE *fp, Graph *a);
int LoadFromFile(FILE *fp, Graph *a);
void Timing(double *add, double *del, double *ser, int n, int reb);
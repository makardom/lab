#pragma once

typedef struct Edge{
    struct Node *node;
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

void InitGraph(Graph **a);
void InitNode(Node *a);
int AddNodeInGraph(Graph *a, Node *add);
int AddEdgeInGraph(Graph *a, int name1, int name2);
int DeleteEdgeInGraph(Graph *a, int name1, int name2);
int DeleteNodeInGraph(Graph *a, int name);
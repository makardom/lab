#ifndef INC_6_BINARYHEAP_H
#define INC_6_BINARYHEAP_H

#include <stdio.h>
#define N 50

typedef struct Infotype{
    float num1;
    float num2;
    char *str;
}Infotype;

typedef struct Node{
    char *key;
    int ver;
    struct Node *left;
    struct Node *right;
    struct Infotype *info;
}Node;

int Right(int i);
int Left(int i);
int Parent(int i);
int size_heap(Node **nodes);
void AddNewElement(Node ***nodes, char *key, Infotype *info, int size);
void Heap_Sort(Node ***nodes, int size);
void CreateLinks(Node ***nodes, int size);
int SearchElement(Node **nodes, char *key, int ver, int size);
int DeleteElement(Node ***nodes, char *key, int ver);
void SaveInFile(Node **a, FILE *fp);
int LoadArrayFromFile(FILE *fp, Node ***a);


#endif //INC_6_BINARYHEAP_H

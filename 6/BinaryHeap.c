#include <stdlib.h>
#include "BinaryHeap.h"
#include "Functions.h"
#include <string.h>
#include <stdio.h>

int Parent(int i){
    return (i-1)/2;
}

int Left(int i){
    return 2*i+1;
}

int Right(int i){
    return 2*i+2;
}

int CheckVer(Node **nodes, char *key, int size){
    int ver = 1;
    for (int i=0; i<size; i++){
        if (strcmp(nodes[i]->key, key)==0 && nodes[i]->ver>=ver)
            ver = nodes[i]->ver+1;
    }
    return ver;
}

int size_heap(Node **nodes){
    int size = 0;
    int i = 0;
    while (nodes[i] != NULL){
        size++;
        i++;
    }
    return size;
}

void AddNewElement(Node ***nodes, char *key, Infotype *info, int size){
    Node *new = (Node *) malloc(sizeof(Node));
    new->info = info;
    new->key = key;
    new->left = NULL;
    new->right = NULL;
    new->ver = CheckVer(*nodes, key, size);
    *nodes = (Node **) realloc(*nodes, (size+2)* sizeof(Node));printf("ok\n");
    (*nodes)[size+1] = NULL;
    (*nodes)[size] = new;
}

void Max_Heapify(Node ***nodes, int i, int size){
    int l = Left(i);
    int r = Right(i);
    int largest = i;
    if (r<size && l<size && strcmp((*nodes)[r]->key, (*nodes)[l]->key)==0 && (*nodes)[r]->ver>(*nodes)[l]->ver) {
        Node *t = (*nodes)[l];
        (*nodes)[l] = (*nodes)[r];
        (*nodes)[r] = t;
    }
    if (l<size && strcmp((*nodes)[l]->key, (*nodes)[i]->key)==0 && (*nodes)[l]->ver>(*nodes)[i]->ver) largest = l;
    if (r<size && strcmp((*nodes)[r]->key, (*nodes)[largest]->key)==0 && (*nodes)[r]->ver>(*nodes)[largest]->ver) largest = r;


    if (l<size && strcmp((*nodes)[l]->key, (*nodes)[i]->key)<0) largest = l;
    if (r<size && strcmp((*nodes)[r]->key, (*nodes)[largest]->key)<0) largest = r;

    if (largest!=i){
        Node *t = (*nodes)[i];
        (*nodes)[i] = (*nodes)[largest];
        (*nodes)[largest] = t;
        Max_Heapify(nodes, largest, size);
    }
}

void Build_Max_Heap(Node ***nodes, int size){
    int i = (size-1)/2;
    while(i>=0){
        Max_Heapify(nodes, i, size);
        i = i-1;
    }
}

void Heap_Sort(Node ***nodes, int size){
    Build_Max_Heap(nodes, size);
    int i = size-1;
    int heapsize = size;
    while (i>=1){
        Node *t = (*nodes)[0];
        (*nodes)[0] = (*nodes)[i];
        (*nodes)[i] = t;
        heapsize = heapsize-1;
        Max_Heapify(nodes, 0, heapsize);
        i -=1;
    }

}

void CreateLinks(Node ***nodes, int size){
    int i=0;
    while (i<size){

        if (Right(i)<size) {
            (*nodes)[i]->right = (*nodes)[Right(i)];
        }else
            (*nodes)[i]->right = NULL;

        if (Left(i)<size) {
            (*nodes)[i]->left = (*nodes)[Left(i)];
        }
        else
            (*nodes)[i]->left = NULL;
        i++;
    }
}

int SearchElement(Node **nodes, char *key, int ver, int size){
    int i=(size-1)/2;
    int m = (size-1)/2;
    while(i>0 && m>=0 && m<size){
        if (strcmp(nodes[m]->key, key)==0 && nodes[m]->ver==ver){
            PrintElement(nodes[m]);
            return 0;
        }
        else if (strcmp(nodes[m]->key, key)==0 && nodes[m]->ver>ver){
            m = m-i;
        }
        else if (strcmp(nodes[m]->key, key)==0 && nodes[m]->ver<ver){
            m = m+i;
        }
        else if (strcmp(nodes[m]->key, key)>0){
            m+=i;
        }
        else if (strcmp(nodes[m]->key, key)<0){
            m-=i;
        }
        if (i!=1)
            i = (i+1)/2;
        else
            i = i/2;
    }
    if (m<0){
        m = 0;
    } else if (m>=size){
        m=size-1;
    }
    if (strcmp(nodes[m]->key, key)==0 && nodes[m]->ver==ver){
        PrintElement(nodes[m]);
        return 0;
    }
    for (int i=0; i<size; i++){
        if (strcmp(nodes[i]->key, key)==0 && nodes[i]->ver==ver){
            PrintElement(nodes[i]);
            return 0;
        }
    }
    return 1;
}

int DeleteElement(Node ***nodes, char *key, int ver){
    int i;
    int size = size_heap(*nodes);
    for (i=0; i<size; i++){
        if (strcmp((*nodes)[i]->key, key)==0 && (*nodes)[i]->ver==ver)
            break;
    }
    if (i==size)
        return 1;
    free((*nodes)[i]->key);
    free((*nodes)[i]->info->str);
    free((*nodes)[i]->info);
    for (;i<size; i++){
        (*nodes)[i] = (*nodes)[i+1];
    }

}

void SaveInFile(Node **a, FILE *fp){
    int size = size_heap(a);
    for (int i=0; i<size; i++){
        fprintf(fp, "%s\n%f %f %s\n", a[i]->key, a[i]->info->num1, a[i]->info->num2, a[i]->info->str);
    }
}

int LoadArrayFromFile(FILE *fp, Node ***a){
    char *key, *str;
    float x, y;
    fseek(fp, 0, SEEK_SET);
    while ((key = readStringFile(fp))!=NULL){
        if (strlen(key)>=N)
            return 1;
        //int pos = ftell(fp);
        fscanf(fp, "%f", &x);
        fscanf(fp, "%f", &y);
        str = readStringFile(fp);
        Infotype *info = (Infotype *) malloc(sizeof(Infotype));
        info->num1 = x;
        info->num2 = y;
        info->str = str;
        int size = size_heap(*a);
        AddNewElement(a, key, info, size);
        size +=1;
        Heap_Sort(a, size);
        CreateLinks(a, size);
    }
    return 0;
}
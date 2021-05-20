#include "Resources.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

int FileOpener(FILE **fpo, FILE **fpc, double a){
    char *read, *put;
    printf("Enter reading file's name:\n");
    if ((read = get_str())==NULL){
        return 0;
    }
    if (a==2){
        if (EnterFile(read, *fpo)==0) return 0;
        return 1;
    }
    printf("Enter file's name, where we push information:\n");
    if ((put = get_str())==NULL){
        return 0;
    }
    *fpo = fopen(read, "r+");
    if (*fpo == NULL) {
        printf(" File couldn't be opened!\n");
        free(read);
        free(put);
        return 0;
    }
    *fpc = fopen(put, "w+");
    free(read);
    free(put);
    return 1;
}

int ReadFromFile(FILE *fpo, int block, Queue **q){
    char *a;
    a = (char *)calloc(block,sizeof(char));
    if (fread(a, sizeof(char),block,fpo)<=0){
        printf("Can't read from file!\n");
        return 0;
    }
    char *b = a;
    for (int i=0; i<block; ++i, ++a) {
        if (push(q, a) == 0) {
            free(b);
            return 0;
        }
    }
    free(b);
    return 1;
}

int QueInFile(Queue *q, FILE *fp, int block){
    char *b;
    b = (char *)malloc(block * sizeof(char));
    char *a = b;
    for (int i=0; i<block; ++i, ++a){
        if (pop(q, a)==0) {
            free(b);
            return 1;
        }
    }
    if (fwrite(b, sizeof(char), block, fp) == 0) {
        printf("Can't be writen\n");
        return 0;
    }
    free(b);
    return 1;
}
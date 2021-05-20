#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef VEC

int push (Queue **vec, char *a) {
    if (*vec == NULL) {
        *vec = (Queue *) calloc(1,sizeof(Queue));
        (*vec)->head = 0;
        (*vec)->tail = 0;
        (*vec)->n = 0;
    }
    if ((*vec)->n == N_MAX) {
        printf("Vector is full\n");
        return 0;
    }
    (*vec)->elem[(*vec)->tail] = *a;
    (*vec)->n++;
    (*vec)->tail = ((*vec)->tail + 1) % N_MAX;
    (*vec)->elem[(*vec)->tail] = '\0';
    //free(a);
    return 1;
}


int pop (Queue *q, char *a){
    if (q==NULL || q->n == 0){
        return 0;
    }
    *a = q->elem[q->head];
    q->head = (q->head +1)%N_MAX;
    q->n--;
    return 1;
}


#endif
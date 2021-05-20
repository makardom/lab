#include <stdlib.h>
#include <time.h>
#include "Queue.h"

#ifndef VEC

int push(Queue **q, char *a){
    if (*q == NULL){
        *q = (Queue *)malloc(sizeof(Queue));
        (*q)->head = NULL;
        (*q)->tail = NULL;
        (*q)->n = 0;
    }
    List *list;
    list = (List *) calloc(1, sizeof(List));
    list->a = *a;
    list->next = NULL;
    if ((*q)->n==0) {
        (*q)->head = list;
        (*q)->tail = list;
        (*q)->n++;
        return 1;
    }
    (*q)->tail->next = list;
    (*q)->tail = list;
    (*q)->n++;
    return 1;
}


int pop(Queue *q, char *a){
    if (q==NULL || q->n == 0)
        return 0;
    *a = q->head->a;
    List *b;
    b = q->head;
    q->head = q->head->next;
    q->n--;
    free(b);
    return 1;
}

#endif

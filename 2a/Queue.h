#ifndef LAB2_2SEM_QUEUE_H
#define LAB2_2SEM_QUEUE_H

#include <stdio.h>
#define N_MAX 500
//#define VEC

#ifdef VEC

typedef struct Queue{
    char elem[N_MAX];
    int n;
    int head;
    int tail;
}Queue;
-
#else

typedef struct List{
    char a;
    struct List *next;
}List;

typedef struct Queue{
    int n;
    List *head;
    List *tail;
} Queue;

#endif

int push(Queue **q, char *a);
int pop(Queue *q, char *a);


#endif //LAB2_2SEM_QUEUE_H

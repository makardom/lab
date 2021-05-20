#include "library.h"

#include <stdio.h>
#include <stdlib.h>



int getInt(int *a){
    int n;
    do {
        n = scanf("%d", a);
        if (n<0)
            return 0;
        if (n==0){
            printf("Error! Return input\n");
            scanf("%*c");
        }
    }while(n==0);
    return 1;
}

int input(Matrix *rm){
    int m;
    int i,j;
    int *p;
    const char *str = "";
    do{
        printf("%s\n", str);
        str = "Repeat enter, please";
        printf("Enter number of lines:");
        if (getInt(&m)==0)
            return 0;
    }while (m<1);
    rm->lines = m;//save number of lines in matrix

    rm->matr = (Line*)calloc(m, sizeof(Line));//memory allocation

    for (i=0; i<rm->lines; ++i){
        str="";
        do{
            printf("%s\n", str);
            printf("Enter number of items in line %d:", i+1);
            str = "Repeat enter, please";
            if (getInt(&m)==0){
                rm->lines=i;
                clear(rm);
                return 0;
            }
        }while(m<1);
        rm->matr[i].n = m;

        p=(int *)malloc(sizeof(int)*m);
        rm->matr[i].a = p;

        printf("Enter items for matrix line #%d:\n", i+1);
        for (j=0; j<m; ++j, ++p) {
            if (getInt(p) == 0) {
                rm->lines = i + 1;
                clear(rm);
                return 0;
            }
        }
    }
    return 1;
}

void output(Matrix *a){
    int i,j;
    int *p=NULL;
    printf("\n");
    for (i=0; i<a->lines; i++){
        p=a->matr[i].a;
        for (j=0; j<a->matr[i].n; ++j, ++p){
            printf("%10d|", *p);
        }
        printf("\n");
    }
}

void clear(Matrix *a){
    int i;
    for (i=0; i<a->lines; ++i)
        free(a->matr[i].a);
    free(a->matr);
    a->lines = 0;
    a->matr = NULL;
}

int countnumb(int a){
    int k=0;
    while(a>0){
        k++;
        a/=10;
    }
    return k;
}

double countnumbln(int *b, int n){//подсчет среднего количества цифр в строке
    int i;
    double res;
    int sum = 0;
    for (i=0; i<n; ++i, ++b){
        sum+=countnumb(*b);
    }
    res = sum/n;
    return res;
}

int countmem(Line a, double m){//количество удовлетворяющих условию элементов строки
    int i,k=0;
    int *p;
    p = a.a;
    for (i=0; i<a.n; ++i, ++p){
        if (countnumb(*p)>m)
            k++;
    }
    return k;
}

void NewMatrix(Matrix *a, Matrix *b, Matrix *c){
    a->matr = (Line *)malloc(b->lines * sizeof(Line));
    a->lines = b->lines;
    c->matr = (Line *)malloc(sizeof(Line)*b->lines);
    c->lines = b->lines;
    int i;
    double k;
    int *p, *q, *r;
    for (i=0; i<b->lines; ++i){
        k = countnumbln(b->matr[i].a, b->matr[i].n);
        a->matr[i].n = countmem(b->matr[i], k);
        c->matr[i].n = b->matr[i].n - a->matr[i].n;
        q = b->matr[i].a;
        p = (int *)malloc(sizeof(int)*a->matr[i].n);
        a->matr[i].a = p;
        r = (int *)malloc(sizeof(int)*c->matr[i].n);
        c->matr[i].a = r;
        for (int j=0; j<b->matr[i].n; ++j, ++q){
            if (countnumb(*q)>k){
                *p = *q;
                ++p;
            }
            else{
                *r = *q;
                ++r;
            }
        }
    }
}

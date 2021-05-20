#pragma once

typedef struct Line{
    int n;
    int *a;
} Line;

typedef struct Matrix{
    int lines;
    Line *matr;
}Matrix;

int getInt(int *);//enter integer numbers
int input(Matrix *a);//enter matrix
double countnumbln(int *b, int n);//counting numbers in one line and calculating the average number
int countnumb(int a);//counting number of digits in a number
int countmem(Line matr, double m);//count number of items which approach
void output(Matrix *a);// matrix output
void clear(Matrix *a); //release the matrix
void NewMatrix(Matrix *a, Matrix *b, Matrix *c);//create new matrix which need to do in task
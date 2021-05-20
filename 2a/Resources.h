#pragma once

#include <stdio.h>
#include "Queue.h"

char *get_str();
int getInt(int *a);
int getDouble(double *a);
int start();
void Menu();
int work(double a);
void EnterInFile(FILE *fp, int k);
void PrintFile(FILE *fp);
int ReadFile();
int EnterFile(char *read, FILE *fpo);
int FileOpener(FILE **fpo, FILE **fpc, double a);
int ReadFromFile(FILE *fpo, int block, Queue **q);
int QueInFile(Queue *q, FILE *fp, int block);

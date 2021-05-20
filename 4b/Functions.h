#pragma once

#include <stdio.h>

void Menu();
int getFloat(float *a);
char *get_str();
int getInt(int *a);
char *readStringFile(FILE *fn);
void D_Start(Tree **a, int choice, Node *Elist);
void FirstChoice(Tree **a, Node *Elist);
void FourthChoice(Tree *a, Node *Elist);
void PrintfTree(Node *a, int kol, Node *Elist);
void PrintElement(Node *a);
void D_LoadTree(Tree *a, Node *Elist);
void D_SaveTreeInFile(Tree *a, Node *Elist);
void PrintTreeOne(Node *a, Node *Elist, char *key);
void PrintTreeTwo(Node *a, Node *Elist);
void D_PrintTreeTwo(Node *a, Node *Elist);
void PrintBigger(Tree *a, Node *Elist, int ver, char *key);
void D_PrintBigger(Tree *a, Node *Elist);
void ThirdChoice(Tree **a, Node *Elist);
void D_Timing(Node *Elist);
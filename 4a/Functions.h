#pragma once

#include "Tree.h"


void Menu();
int getFloat(float *a);
char *get_str();
int getInt(int *a);
void D_Start(Tree **a, int choice);
void FirstChoice(Tree **a);
void ThirdChoice(Tree **a);
void FourthChoice(Tree **a);
void PrintfTree(Item *a, int kol);
void PrintElement(Item *a);
char *readStringFile(FILE *fn);
void D_LoadTree(Tree *a);
void D_SaveTreeInFile(Tree *a);
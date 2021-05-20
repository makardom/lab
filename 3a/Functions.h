#ifndef LAB3_SEM2_FUNCTIONS_H
#define LAB3_SEM2_FUNCTIONS_H
#include "Table.h"
#include "TableFile.h"
#define N 50

#define B

#ifdef B

char *get_str();
int getUnsInt(unsigned int *a);
int MainFunc(Table **table, unsigned int a, FILE *fp);
void Menu();
void TableInit(Table **table);
int hash(unsigned int key);
int FirstChoice(Table **a);
void ForCase4(Table *a);
void SecondChoice(Table *a);
void ThirdChoice(Table **a);
void SixChoice(Table **a);
void DeleteTable(Table *a);
void D_SaveTable(Table *table);
void D_InitFileKey(FILE **fp, char *name);
void D_InitFileInfo(FILE **fp, char *name);

#else

int MainFunc(Table **table, unsigned int a);
int FirstChoice(Table **a);
void ForCase4(Table *a);
void SecondChoice(Table *a);
void ThirdChoice(Table **a);
void SixChoice(Table **a);

#endif
#endif //LAB3_SEM2_FUNCTIONS_H
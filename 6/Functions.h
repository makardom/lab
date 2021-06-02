#ifndef INC_6_FUNCTIONS_H
#define INC_6_FUNCTIONS_H

int getFloat(float *a);
int getInt(int *a);
char *get_str();
void Menu();
void D_Start(Node ***array, int choice);
void D_AddNewElement(Node ***array);
void PrintBinaryHeap(Node *a, int kol, int size);
void D_DeleteElement(Node ***array);
void PrintTreeTwo(Node *a, int size);
void D_SearchElement(Node **a);
void PrintElement(Node *a);
void PrintBigger(Node **a);
void D_SaveInFile(Node **a);
void D_LoadFromFile(Node ***a);
char *readStringFile(FILE *fn);
void PrintAsArray(Node **nodes,int size);

#endif //INC_6_FUNCTIONS_H

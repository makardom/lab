#include <stdio.h>
#include "Functions.h"
#include "Table.h"
#include "TableFile.h"

#ifndef B
int main(){
    int flag =1;
    Table *tab=NULL;
    while(flag) {
        Menu();
        unsigned int choice;
        if (getUnsInt(&choice) == 0)
            return 0;
        scanf("%*c");
        if (choice<1 || choice > 7)
            printf("Error! Enter right number from list:\n");
        else if (choice == 7) {
            DeleteTable(tab);
            flag = 0;
        }
        else
            if (MainFunc(&tab, choice)==3)
                return 0;
    }
    return 1;
}

#else

int main(){
    int flag =1;
    Table *tab=NULL;
    FILE *fp = NULL;
    FILE *finfo = NULL;
    if (D_TakeTable(&tab, &fp) == -1){
//        D_InitFileKey(&fp);
//        DeleteTable(tab);
        return -1;
    }
    while(flag) {
        Menu();
        unsigned int choice;
        if (getUnsInt(&choice) == 0)
            return 0;
        scanf("%*c");
        if (choice<1 || choice > 7)
            printf("Error! Enter right number from list:\n");
        else if (choice == 7) {
            D_SaveTable(tab);
            DeleteTable(tab);
            flag = 0;
        }
        else
        if (MainFunc(&tab, choice, fp)==0)
            return 0;
    }
//
//    if (fp != NULL)
//        fclose(fp);
    return 1;
}
#endif
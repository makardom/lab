#include <stdio.h>
#include "Tree.h"
#include "Functions.h"
#include <string.h>

int main() {
    Tree *tree = NULL;
    TreeInit(&tree);
    int flag = 1;
    while (flag){
        Menu();
        int choice;
        if (getInt(&choice)==-1){
            printf("Input Error!\n");
            continue;
        }
        scanf("%*c");
        if (choice==10){
            printf("Goodbye!\n");
            DeleteTree(&tree);
            flag = 0;
        }else if (choice>0&&choice<10){
            D_Start(&tree, choice);
        }
    }
    return 0;
}
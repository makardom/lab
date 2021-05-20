#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"
#include "Functions.h"

int main() {
    Tree *tree = NULL;
    Node *Elist = (Node *) malloc(sizeof(Node));
    Elist->info = NULL;
    Elist->parent = Elist;
    Elist->key = NULL;
    Elist->right = Elist;
    Elist->left = Elist;
    Elist->color = BLACK;
    TreeInit(&tree, Elist);
    int flag = 1;
    while (flag){
        Menu();
        int choice;
        if (getInt(&choice)==-1){
            printf("Input Error!\n");
            continue;
        }
        scanf("%*c");
        if (choice==11){
            printf("Goodbye!\n");
            DeleteTree(&tree, Elist);
            flag = 0;
        }else if (choice>0&&choice<11){
            D_Start(&tree, choice, Elist);
        }
    }
}
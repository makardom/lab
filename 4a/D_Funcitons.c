#include "Tree.h"
#include "Functions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void Menu(){
    printf("1. Add new Node\n2. Load from file\n3. Delete node by key(ver)\n4. Search element by key\n5. Print tree\n6. Print in direct view\n7. Print the largest key\n8. Save tree in file\n9. Timing\n10. Exit\n");
    printf("Enter your choice:");
}

void D_Start(Tree **a, int choice){
    int kol=0;
    switch(choice) {
        case 1:
            FirstChoice(a);
            break;
        case 2:
            D_LoadTree(*a);
            break;
        case 3:
            ThirdChoice(a);
            break;
        case 4:
            FourthChoice(a);
            break;
        case 5:
            PrintfTree((*a)->node, kol);
            break;
        case 6:
            PrintTreeTwo((*a)->node);
            break;
        case 7:
            PrintBigger(*a);
            break;
        case 8:
            D_SaveTreeInFile(*a);
            break;
        case 9:
            D_Timing();
            break;
    }
}

void FirstChoice(Tree **a){
    printf("Enter key:\n");
    char *key;
    if ((key=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    if (strlen(key)+1>N){
        printf("key is longer, than necessary\n");
        return;
    }
    printf("Enter 1-st float number:\n");
    float num1, num2;
    if (getFloat(&num1)==-1){
        printf("Input Error\n");
        free(key);
        return;
    }
    scanf("%*c");
    printf("2-nd number:\n");
    if (getFloat(&num2)==-1){
        printf("Input Error\n");
        free(key);
        return;
    }
    scanf("%*c");
    printf("Enter string info:\n");
    char *string;
    if ((string=get_str())==NULL){
        printf("Input Error\n");
        free(key);
        return;
    }
    Info *info;
    info = (Info *) malloc(sizeof(Info));
    info->num1 = num1;
    info->num2 = num2;
    info->str = string;
    printf("ok\n");
    AddNodeInTree(*a, info, key);
}

void ThirdChoice(Tree **a){
    printf("Enter key you want delete:\n");
    char *key;
    if ((key=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    printf("Enter ver of this key:\n");
    int ver;
    if (getInt(&ver)==-1){
        free(key);
        printf("Input Error!\n");
        return;
    }
    if (DeleteElement(*a, key, ver)==1){
        printf("Element not found\n");
        return;
    }
}

void FourthChoice(Tree **a){
    printf("Enter key what you search:\n");
    char *key;
    if ((key=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    if (strlen(key)+1>N){
        free(key);
        printf("key is longer, than necessary\n");
        return;
    }
    printf("Enter version:\n");
    int ver;
    if (getInt(&ver)==-1){
        free(key);
        printf("Input Error!\n");
        return;
    }
    scanf("%*c");
    if (SearchElement(*a, key, ver)==0){
        printf("Element not found\n");
    }
    free(key);
}

void PrintElement(Item *a){
    printf("--%s    Info: %0.2f    %0.2f    %s    ver: %d\n", a->key, a->info->num1, a->info->num2, a->info->str, a->ver);
}

void PrintfTree(Item *a, int kol){
    kol+=1;
    int i=kol;
    if (a!=NULL){
        PrintfTree(a->right, kol);
        while (i>0){
            printf("    ");
            i--;
        }
        PrintElement(a);
        PrintfTree(a->left, kol);
    }
}

void PrintTreeTwo(Item *a){
    if (a!=NULL){
        PrintTreeTwo(a->left);
        PrintElement(a);
        PrintTreeTwo(a->right);
    }
}

void PrintBigger(Tree *a){
    if (a->node!=NULL){
        Item *node = a->node;
        while (node->right!=NULL){
            node = node->right;
        }
        PrintElement(node);
        return;
    }
    printf("In tree no element with the largest key\n");
}

void D_LoadTree(Tree *a){
    printf("Enter file's name:");
    char *name;
    if ((name=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    FILE *fp;
    if ((fp = fopen (name, "r"))==NULL){
        free(name);
        printf("File cannot be opened\n");
        return;
    }
    if(LoadTree(fp, a)==1){
        free(name);
        printf("key is longer, than necessary\n");
        printf("Reload file\n");
    }
    fclose(fp);
    free(name);
}

void D_SaveTreeInFile(Tree *a){
    printf("Enter file's name to record:\n");
    char *name;
    if ((name=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    FILE *fp;
    if((fp = fopen(name, "w"))==NULL){
        printf("File cannot be open\n");
        free(name);
    }
    fseek(fp, 0, SEEK_SET);
    SaveInFile(fp, a->node);
    fclose(fp);
    free(name);
}

char *get_str(){
    char buf[50] = {0};
    char *res= NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%49[^\n]", buf);
        if (n<0){
            if (!res) {
                return NULL;
            }
        }
        else if (n>0){
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while(n>0);

    if (len>0){
        res[len]='\0';
    } else{
        res = calloc(1, sizeof(char));
    }

    return res;
}

int getFloat(float *a){
    int n;
    do{
        n = scanf("%f", a);
        if (n<0)
            return -1;
        if (n==0){
            printf("Error! Return input\n");
            scanf("%*c");
        }
    } while (n==0);
    return 1;
}
int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if (n<0)
            return -1;
        if (n==0){
            printf("Error! Return input\n");
            scanf("%*c");
        }
    } while (n==0);
    return 1;
}

char *readStringFile(FILE *fn) {
    char buf[50] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = fscanf(fn,"%49[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(fn,"%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}
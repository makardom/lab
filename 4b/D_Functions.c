#include "RBTree.h"
#include "Functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Menu(){
    printf("1. Add new Node\n2. Load from file\n3. Delete node by key(ver)\n4. Search element by key\n5. Print tree\n6. Print in direct view\n7. Print the largest key\n8. Save tree in file\n9. Timing\n10. Visualization\n11. Exit\n");
    printf("Enter your choice:");
}

void D_Start(Tree **a, int choice, Node *Elist){
    int kol=0;
    switch(choice) {
        case 1:
            FirstChoice(a, Elist);
            break;
        case 2:
            D_LoadTree(*a, Elist);
            break;
        case 3:
            ThirdChoice(a, Elist);
            break;
        case 4:
            FourthChoice(*a, Elist);
            break;
        case 5:
            PrintfTree((*a)->node, kol, Elist);
            break;
        case 6:
            D_PrintTreeTwo((*a)->node, Elist);
            break;
        case 7:
            D_PrintBigger(*a, Elist);
            break;
        case 8:
            D_SaveTreeInFile(*a, Elist);
            break;
        case 9:
            D_Timing(Elist);
            break;
        case 10:
            Visualization((*a)->node, Elist, (*a)->size);
    }
}

void FirstChoice(Tree **a, Node *Elist){
    printf("Enter key:\n");
    char *key;
    if ((key=get_str())==NULL){
        printf("Input Error!\n");
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
    AddNodeInTree(*a, info, key, Elist);
}

void ThirdChoice(Tree **a, Node *Elist){
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
    if (DeleteNode(*a, key, ver, Elist)==1){
        printf("This element is absent.\n");
    }
}

void FourthChoice(Tree *a, Node *Elist){
    printf("Enter key what you search:\n");
    char *key;
    if ((key=get_str())==NULL){
        printf("Input Error!\n");
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
    if (SearchElement(a, key, ver, Elist)==1){
        printf("Element not found\n");
    }
    free(key);
}

void PrintElement(Node *a){
    if (a->color==0)
        printf("--%s  black  Info: %0.2f    %0.2f    %s    ver: %d\n", a->key, a->info->num1, a->info->num2, a->info->str, a->ver);
    else
        printf("--%s  red    Info: %0.2f    %0.2f    %s    ver: %d\n", a->key, a->info->num1, a->info->num2, a->info->str, a->ver);
}

void PrintfTree(Node *a, int kol, Node *Elist){
    kol+=1;
    int i=kol;
    if (a!=Elist){
        PrintfTree(a->right, kol, Elist);
        while (i>0){
            printf("    ");
            i--;
        }
        PrintElement(a);
        PrintfTree(a->left, kol, Elist);
    }
}

void D_PrintTreeTwo(Node *a, Node *Elist){
    printf("Do you want enter lower border?(1-yes, 0-no):");
    int ch;
    if (getInt(&ch)==-1){
        printf("Input Error!\n");
        return;
    }
    scanf("%*c");
    if (ch==1) {
        printf("Enter the key of the lower border:\n");
        char *key;
        if ((key = get_str()) == NULL) {
            printf("Input Error!\n");
            return;
        }
        PrintTreeOne(a, Elist, key);
        free(key);
        return;
    } else if (ch==0){
        PrintTreeTwo(a, Elist);
        return;
    }
    printf("You entered the wrong number. Try again!\n");
}

void PrintTreeOne(Node *a, Node *Elist, char *key){
    if (a!=Elist){
        PrintTreeOne(a->left, Elist, key);
        if (strcmp(a->key, key)>0){
            PrintElement(a);
        }
        PrintTreeOne(a->right, Elist, key);
    }
}

void PrintTreeTwo(Node *a, Node *Elist){
    if (a!=Elist){
        PrintTreeTwo(a->left, Elist);
        PrintElement(a);
        PrintTreeTwo(a->right, Elist);
    }
}

void D_PrintBigger(Tree *a, Node *Elist){
    printf("Enter the key of the higher border:\n");
    char *key;
    if ((key = get_str()) == NULL) {
        printf("Input Error!\n");
        return;
    }
    printf("Enter version of the biggest key:\n");
    int ver;
    if (getInt(&ver)==-1){
        printf("Input Error!\n");
        return;
    }
    scanf("%*c");
    PrintBigger(a, Elist, ver, key);
    free(key);
}

void PrintBigger(Tree *a, Node *Elist, int ver, char *key){
    if (a->node!=Elist){
        Node *node = a->node;
        while (node!=Elist && strcmp(node->key, key)>0){
            node = node->left;
        }
        if (node==Elist){
            printf("There are no elements less than the specified one\n");
            return;
        }
        while (node->right!=Elist && strcmp(node->right->key, key)<=0){
            node = node->right;
        }
//        if (node == Elist){
//            printf("There are no elements less than the specified one\n");
//            return;
//        }

        char *serkey = node->key;
        if (SearchElement(a, serkey, ver, Elist)==1){
            printf("This version not found in tree\n");
        }
        return;
    }
    printf("In tree no element with the largest key\n");
}

void D_LoadTree(Tree *a, Node *Elist){
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
    if(LoadTree(fp, a, Elist)==1){
        //free(name);
        printf("Reload file\n");
    }
    fclose(fp);
    free(name);
}

void D_SaveTreeInFile(Tree *a, Node *Elist){
    printf("Enter file's name to record:\n");
    char *name;
    if ((name=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    FILE *fp;
    if((fp = fopen(name, "w"))==NULL){
        printf("File cannot be open\n");
        free(name); return;
    }
    fseek(fp, 0, SEEK_SET);
    SaveInFile(fp, a->node, Elist);
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

void PrintInfoDotfile(Node *node, Info *info, FILE *fp){
    fprintf(fp, "%.0f %.0f %s ver:%d\"", info->num1, info->num2, info->str, node->ver);
}

void PrintDotfile(Node *node, FILE *fp){
    fprintf(fp, "   \"%s ", node->key);
    PrintInfoDotfile(node, node->info, fp);
}

void PrintElist(Node *node, FILE* fp)
{
    PrintDotfile(node, fp);
    fprintf(fp, " -> \"Elist\"\n");
}

void PrintNodeDOT(Node *node, FILE* fp, Node *Elist)
{
    if (node->left != Elist)
    {
        PrintDotfile(node, fp);
        fprintf(fp, " -> ");
        PrintDotfile(node->left, fp);
        fprintf(fp, "\n");
        PrintNodeDOT(node->left, fp, Elist);
    }
    else
        PrintElist(node, fp);

    if (node->right != Elist)
    {
        PrintDotfile(node, fp);
        fprintf(fp, " -> ");
        PrintDotfile(node->right, fp);
        fprintf(fp, "\n");
        PrintNodeDOT(node->right, fp, Elist);
    }
    else
        PrintElist(node, fp);
}

void PrintfNodePos(Node *node, FILE *fp, float x, float y, float z, Node *Elist){
    if (node!=Elist) {
        fprintf(fp, "   \"%s ", node->key);
        PrintInfoDotfile(node, node->info, fp);
        if (node->color==BLACK) {
            fprintf(fp, " [pos = \"%.2f, %.2f!\"][color = black]\n", x, y);
        } else if (node->color==RED){
            fprintf(fp, " [pos = \"%.2f, %.2f!\"][color = red]\n", x, y);
        }
        PrintfNodePos(node->left, fp, x-z, y-z, z-z/2, Elist);
        PrintfNodePos(node->right, fp, x+z, y-z, z-z/2, Elist);
    }
}

int Visualization(Node *node, Node *Elist, int k){
    FILE *fp = NULL;
    if ((fp = fopen("llrb.dot", "w+"))==NULL){
        printf("Can't create file\n");
        return 1;
    }
    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "digraph LLRB {\n");
    fprintf(fp, "   \"Elist\" [pos = \"%d,0!\"]\n", k);
    PrintfNodePos(node, fp, 2*k, 2*k, 4, Elist);

    if (node == Elist)
        fprintf(fp, "\n");
    else if (node->right == NULL && node->left == NULL){
        PrintDotfile(node, fp);
        fprintf(fp, "\n");
    }
    else
        PrintNodeDOT(node, fp, Elist);
    fprintf(fp, "}\n");

    fclose(fp);

    system("dot -Kfdp -n -Tpng -o llrb.png llrb.dot");
    return 0;
}
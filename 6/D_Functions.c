#include "BinaryHeap.h"
#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu(){
    printf("0. Exit\n1. Add new Node\n2. Load from file\n3. Delete node by key(ver)\n4. Search element by key\n5. Print tree\n6. Print in direct view\n7. Print the largest key\n8. Save tree in file\n9. Print Array\n");
    printf("Enter your choice:");
}

void D_Start(Node ***array, int choice) {
    if (*array == NULL){
//        *array = (Node **) malloc(sizeof(Node*));
//        **array = (Node *) calloc(1, sizeof(Node));
        *array = (Node **) calloc(1, sizeof(Node));
        //**array = NULL;
    }
    int kol =0;
    switch (choice) {
        case 1:
            D_AddNewElement(array);
            break;
        case 2:
            D_LoadFromFile(array);
            break;
        case 3:
            D_DeleteElement(array);
            break;
        case 4:
            D_SearchElement(*array);
            break;
        case 5:
            PrintBinaryHeap(**array, kol, size_heap(*array));
            break;
        case 6:
            PrintTreeTwo(*array[0], size_heap(*array));
            break;
        case 7:
            PrintBigger(*array);
            break;
        case 8:
            D_SaveInFile(*array);
            break;
        case 9:
            PrintAsArray(*array, size_heap(*array));
            break;
    }
}

void D_AddNewElement(Node ***array){
    printf("Enter key(string with number of symbols less than %d):", N);
    char *key;
    if ((key=get_str())==NULL){
        printf("Input error!\n");
        return;
    }
    if (strlen(key)>=N){
        printf("Number of symbols more than need\n");
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
    Infotype *info;
    info = (Infotype *) malloc(sizeof(Infotype));
    info->num1 = num1;
    info->num2 = num2;
    info->str = string;
    int size = size_heap(*array);
    AddNewElement(array, key, info, size);
    size +=1;
    Heap_Sort(array, size);
    CreateLinks(array, size);
//    PrintBinaryHeap((*array)[0], 0, size);
}

void D_DeleteElement(Node ***array){
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
    if (DeleteElement(array, key, ver)==1){
        printf("Element not found\n");
        return;
    }
    int size = size_heap(*array);
    CreateLinks(array, size);

    free(key);
}

void D_SearchElement(Node **a){
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
    int size = size_heap(a);
    if (SearchElement(a, key, ver, size)==1){
        printf("Element not found\n");
        free(key);
        return;
    }
    free(key);
}

void PrintElement(Node *a){
    printf("--%s    Info: %0.2f    %0.2f    %s    ver: %d\n", a->key, a->info->num1, a->info->num2, a->info->str, a->ver);
}

void PrintBinaryHeap(Node *a, int kol, int size){
    if (size==0){
        printf("No elements\n");
        return;
    }
    kol++;
    int i=kol;
    if (a!=NULL){
        PrintBinaryHeap(a->right, kol, size);
        while (i>0){
            printf("    ");
            i--;
        }
        PrintElement(a);
        PrintBinaryHeap(a->left, kol, size);
    }
}

void PrintTreeTwo(Node *a, int size){
    if (size==0){
        printf("No elements\n");
        return;
    }
    if (a!=NULL){
        PrintElement(a);
        PrintTreeTwo(a->left, size);
        PrintTreeTwo(a->right, size);
    }
}

void PrintAsArray(Node **nodes,int size){
    for (int i=0; i<size; i++){
        PrintElement(nodes[i]);
    }
}

void PrintBigger(Node **a){
    printf("Enter version:\n");
    int ver;
    if (getInt(&ver)==-1){
        printf("Input Error!\n");
        return;
    }
    scanf("%*c");
    int i=0;
    char *key = a[i]->key;
    while (strcmp(a[i]->key, key)==0){
        if (a[i]->ver == ver){
            PrintElement(a[i]);
            return;
        }
        i++;
    }
    printf("No this version of the largest number\n");
}

void D_SaveInFile(Node **a){
    FILE *fp;
    printf("Enter file's name to record information\n");
    char *name;
    if ((name = get_str())==NULL){
        printf("Input error\n");
        return;
    }
    if((fp = fopen(name, "w+"))==NULL){
        printf("File cannot be open\n");
        free(name);
        return;
    }
    fseek(fp, 0, SEEK_SET);
    SaveInFile(a, fp);
    fclose(fp);
    free(name);
}

void D_LoadFromFile(Node ***array){
    FILE *fp;
    printf("Enter file's name where you want read information:\n");
    char *name;
    if ((name = get_str())==NULL){
        printf("Input error\n");
        return;
    }

    if ((fp = fopen (name, "r"))==NULL){
        free(name);
        printf("File cannot be opened\n");
        return;
    }
    if (LoadArrayFromFile(fp, array)==1){
        free(name);
        printf("key is longer, than necessary\n");
        printf("Reload file\n");
        return;
    }

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

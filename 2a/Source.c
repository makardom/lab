#include "Resources.h"
#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int work(double a) {
    if (a==3){
        if (ReadFile()==0)
            return 0;
        return 1;
    }
    FILE *fpo=NULL, *fpc=NULL;
    if (FileOpener(&fpo, &fpc, a)==0)
        return 0;
    printf("Enter block size in byte:\n");
    int block;
    if (getInt(&block) == 0){
        return 0;
    }
    scanf("%*c");
    long int fsize;
    fseek(fpo, 0, SEEK_END);
    fsize = ftell(fpo);
    fseek(fpo, 0, SEEK_SET);
    Queue *q = NULL;
    int random;
    srand(time(NULL));
    int inque =0;
    int block1;
    block1=block;
    while (fsize>0 || inque>0){
        if (block>fsize && fsize!=0){
            block = fsize;
        } else {
            block = block1;
        }
        random = rand()%4;
        if (random==0 && fsize>0){
            if (ReadFromFile(fpo, block, &q)==0){
                fclose(fpo); fclose (fpc); free(q);
                return 0;
            }
            inque += block;
            fsize-=block;
        }
        random = rand()%4;
        if (block >= inque && inque != 0) {
            block = inque;
        } else block = block1;
        if (random>0){
                if (QueInFile(q, fpc, block) == 0) {
                    fclose(fpo); fclose (fpc); free(q);
                    return 0;
                }
                if (inque != 0) inque -= block;
        }
    }
    free(q);
    fclose(fpo);
    fclose(fpc);
    return 1;
}

void Menu(){
    printf("Menu:\n");
    printf("0. Exit\n");
    printf("1. Start work\n");
    printf("2. Creat new file\n");
    printf("3. Read file\n");
}

int start() {
    int flag = 1;
    while (flag) {
        Menu();
        printf("Enter your choice:");
        double choice;
        if (getDouble(&choice) == 0)
            return 0;
        scanf("%*c");
        if (choice==1 || choice==2 || choice==3) {
            if (work(choice) == 0)
                return 0;
        } else if (choice==0) {
            printf("Goodbye!\n");
            flag=0;
        } else printf("Enter correct number from Menu!\n");
    }
    return 1;
}

int EnterFile(char *read, FILE *fpo){
    printf("Enter number of bytes to write in file:\n");
    int k;
    if (getInt(&k)==0) return 0;
    scanf("%*c");
    fpo = fopen(read, "w+");
    EnterInFile(fpo, k);
    free(read);
    fclose(fpo);
    return 1;
}

void EnterInFile(FILE *fp, int k){
    printf("Enter the line you want to add to the file:\n");
    char *a;
    a = get_str();
    if (strlen(a)<k)
        fwrite(a, sizeof(char), strlen(a), fp);
    else fwrite(a, sizeof(char), k, fp);
    free(a);
}

void PrintFile(FILE *fp){
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char *a, *b;
    a=(char *) malloc(size*sizeof(char));
    b = a;
    fread(a, sizeof(char), size, fp);
    for (int i=0; i<size; ++i, ++a)
        printf("%c", *a);
    printf("\n");
    free(b);
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

int getInt(int *a){
    int n;
    do{
        n = scanf("%d", a);
        if (n<0)
            return 0;
        if (n==0){
            printf("Error! Return input\n");
            scanf("%*c");
        }
    } while (n==0);
    return 1;
}

int getDouble(double *a){
    double n;
    do{
        n = scanf("%lf", a);
        if (n<0)
            return 0;
        if (n==0){
            printf("Error! Return input\n");
            scanf("%*c");
        }
    } while (n==0);
    return 1;
}

int ReadFile(){
    FILE *fp;
    char *check;
    printf("Enter name of file to read:\n");
    if ((check = get_str())==NULL){
        return 0;
    }
    if ((fp = fopen (check, "r+"))==NULL){
        printf(" File couldn't be opened!\n");
        free(check);
        return 0;
    }
    PrintFile(fp);
    free(check);
    fclose(fp);
    return 1;
}
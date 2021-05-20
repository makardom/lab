#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "TableFile.h"

#ifdef B

int D_TakeTable(Table **table, FILE **fp){
    TableInit(table);
    FILE *finfo;
    int flag = 0;
    printf("Enter file's name with keys:");
    char *name, *nameinfo;
    if ((name=get_str())==NULL){
        printf("Input Error\n");
        return -1;
    }
    if (OpenFile(fp, name)==0){
        printf("File with keys cannot be open\n");
        D_InitFileKey(fp, name);
        flag++;
    }
    printf("Enter file's name with information:");
    if ((nameinfo=get_str())==NULL){
        printf("Input Error\n");
        free(name);
        return -1;
    }
    if (OpenFile(&finfo, nameinfo)==0){
        printf("File with information cannot be open\n");
        D_InitFileInfo(&finfo, nameinfo);
        flag++;
    }
    (*table)->keys = *fp;
    (*table)->info = finfo;
    if (flag>0){
        free(name);
        free(nameinfo);
        fseek(*fp, 0, SEEK_SET);
        return 2;
    }
    fseek(*fp, 0, SEEK_SET);
    int kol;
    fread(&kol, sizeof(int), 1, *fp);
    for (int i=0; i<kol; ++i){
        int offsetkey, length, infoff, inflen;
        unsigned int key2;
        fread(&offsetkey, sizeof(int), 1, *fp);
        fread(&length, sizeof(int), 1, *fp);
        fread(&key2, sizeof(unsigned int), 1, *fp);
        fread(&infoff, sizeof(int), 1, *fp);
        fread(&inflen, sizeof(int), 1, *fp);
//        char *info1, *info2;
//        TakeInfo(finfo, infoff, inflen, &info1, &info2);
        char *key1;
        key1 = TakeKey1(*fp, offsetkey, length);
        if (EnterElement(*table, key1, key2, infoff, inflen)==0){
            printf("Error! This keys are already available!\n");
            free(key1);
        }
    }
    free(name);
    free(nameinfo);
    return 2;
}

void D_SaveTable(Table *table){
    FILE *fp = table->keys;
    RecordTable(fp, table);
    fclose(fp);
    fclose(table->info);
}

void D_InitFileKey(FILE **fp, char *name){
    if(OpenFileToRecord(fp, name)==0){
        printf("File can't be opened\n");
        free(name);
        return;
    }
    int i=0;
    fwrite(&i, sizeof(int), 1, *fp);
    free(name);
}

void D_InitFileInfo(FILE **fp, char *name){
    if(OpenFileToRecord(fp, name)==0){
        printf("File can't be opened\n"); free(name);
        return;
    }
    char i = '\0';
    fwrite(&i, sizeof(char), 1, *fp);
}

void Menu(){
    printf("1. Enter element in a table\n");
    printf("2. Search element with composite key\n");
    printf("3. Delete element from table with composite key\n");
    printf("4. Search element in table by any given key\n");
    printf("5. Output table in console\n");
    printf("6. Delete elements by any keyspace\n");
    printf("7. Exit\n");
    printf("Enter your choice:\n");
}

int MainFunc(Table **table, unsigned int a, FILE *fp){
    switch (a) {
        case 1: //Enter element in a table
            if (FirstChoice(table) == 0){
                return 0;
            }
            break;
        case 2://Search element with composite key
            SecondChoice(*table);
            break;
        case 3://Delete element from table with composite key
            ThirdChoice(table);
            break;
        case 4://Search element in table by any given key
            ForCase4(*table);
            break;
        case 5: //Output table in console
            PrintTableConsole(*table);
            break;
        case 6:
            SixChoice(table);
            break;
    }
    return 1;
}

int FirstChoice(Table **a){
    if (*a == NULL)
        TableInit(a);
    printf("Enter 1-st key(a string with variable length (null-terminated)):\n");
    char *key1=NULL;
    if ((key1=get_str())==NULL) {
        printf("Input error!\n");
        return 0;
    }
    printf("Enter 2-nd key(a unsigned integer):\n");
    unsigned int key2;
    if (getUnsInt(&key2)==0){
        printf("Input error!\n");
        return 0;
    }
    scanf("%*c");
    printf("Enter 1-st string with Information:\n");
    char *inf1 = NULL;
    if ((inf1=get_str())==NULL){
        printf("Input error!\n");
        free(key1);
        return 0;
    }
    printf("Enter 2-nd string with Information:\n");
    char *inf2=NULL;
    if ((inf2=get_str())==NULL){
        printf("Input error!\n");
        free(key1); free(inf1);
        return 0;
    }
    int infoffset, infolength;
    infolength = (int) strlen(inf1) +1 + (int) strlen(inf2) +1;
    fseek((*a)->info, 0, SEEK_END);
    infoffset = ftell((*a)->info);
    if (EnterElement(*a, key1, key2, infoffset, infolength)==0){
        printf("Error! This keys are already available!\n");
        free(key1); free(inf1); free(inf2);
        return 1;
    }
    PushInfoInFile(*a, inf1, inf2);
    return 1;
}

void SecondChoice(Table *a){
    printf("Enter 1-st key(string):\n");
    char *key1 = NULL;
    if ((key1=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    printf("Enter 2-nd key(uns int):\n");
    unsigned int key2;
    if (getUnsInt(&key2)==-1){
        printf("Input Error!\n"); free(key1);
        return;
    }
    scanf("%*c");
    if (SearchElementByTwoKey(a, key1, key2)==0){
        printf("This composite keys are not defined\n");
    }
    free(key1);
}

void ThirdChoice(Table **a){
    printf("Enter 1-st key(a string with variable length (null-terminated)):\n");
    char *key1 = NULL;
    if ((key1=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    printf("Enter 2-nd key(unsigned int):\n");
    unsigned int key2;
    if ((getUnsInt(&key2))==-1){
        printf("Input Error!\n"); free(key1);
        return;
    }
    scanf("%*c");
    if (DeleteByTwoKeys(*a, key1, key2)==0){
        printf("This composite keys are not defined\n"); free(key1);
        return;
    }
    free(key1);
}

void ForCase4(Table *a){
    printf("Choice keyspace: 1 or 2\n");
    unsigned int ch;
    if (getUnsInt(&ch)==0){
        printf("Input Error!\n");
        return;
    }
    scanf("%*c");
    if (ch==1){
        printf("Enter key(a string with variable length (null-terminated)):\n");
        char *key = NULL;
        if ((key=get_str())==NULL){
            printf("Input Error!\n");
            return;
        }
        printf("Enter version(int), without version(0):\n");
        unsigned int ver;
        if ((getUnsInt(&ver))==-1){
            printf("Input Error!\n"); free(key);
            return;
        }
        scanf("%*c");
        if (ver == 0) {
            SearchSpace1Without(a, key);
            free(key);
        } else if (ver>0){
            SearchSpace1WithVer(a, key, ver);
            free(key);
        }
    } else if (ch==2){
        printf("Enter key(unsigned int):\n");
        unsigned int key;
        if ((getUnsInt(&key))==-1){
            printf("Input Error!\n");
            return;
        }
        scanf("%*c");
        printf("Enter version(int), without version(0):\n");
        unsigned int ver;
        if ((getUnsInt(&ver))==-1){
            printf("Input Error!\n");
            return;
        }
        scanf("%*c");
        if (ver == 0) {
            SearchSpace2Without(a, key);
        } else if (ver>0){
            SearchSpace2WithVer(a, key, ver);
        }
    }
}

void SixChoice(Table **a){
    printf("Choice Keyspace(1 or 2):\n");
    unsigned int space;
    if (getUnsInt(&space)==-1){
        printf("Input Error\n");
        return;
    }
    scanf("%*c");
    if (space==1) {
        printf("Enter 1-st key (string):\n");
        char *key1 = NULL;
        if ((key1 = get_str()) == NULL) {
            printf("Input Error\n");
            return;
        }
        printf("Enter version (0 - if all):\n");
        unsigned int ver;
        if (getUnsInt(&ver) == -1) {
            printf("Input Error\n"); free(key1);
            return;
        }
        scanf("%*c");
        if (ver == 0) {
            if (DeleteElementsBySpace1(*a, key1) == 0) {
                printf("There is no such key in the table\n");
                free(key1);
                return;
            }
        } else {
            if (DeleteElementVerBySpace1(*a, key1, ver) == 0) {
                printf("There is no such element\n");
                free(key1);
                return;
            }
        }
        free(key1);
    } else if (space==2){
        printf("Enter 2-nd key(uns Int):\n");
        unsigned int key2;
        if (getUnsInt(&key2)==-1){
            printf("Input Error\n");
            return;
        }
        scanf("%*c");
        if (DeleteElementsBySpace2(*a, key2) == 0) {
            printf("There is no such key in the table\n");
            return;
        }
    }
}

void PrintTableConsole(Table *table){
    if (table == NULL) {
        printf("Table is empty\n");
        return;
    }
    int k = table->csize1;
    if (k==0){
        printf("Table is empty\n");
        return;
    }
    KeySpace1 *ks1 = table->ks1;
    Item *item = NULL;
    if (ks1 != NULL)
        item = ks1->item;
    int i=1;
    FILE *finfo = table->info;
    while(k>0){
        if (item != NULL && ks1 != NULL) {
            char *info1, *info2;
            char *full = TakeInfo(finfo, ks1->item->infooffset, ks1->item->length, &info1, &info2);
            printf("Element %d:\n", i);
            printf("    Key 1: %s", ks1->key1);
            printf("    Key 1 version: %d\n", ks1->ver);
            printf("    Key 2: %u", item->key2->key2);
            printf("    Key 2 version: %d\n", item->ver2);
            printf("    Value:\n    1 string: %s\n    2 string: %s\n", info1, info2);
            free(full);
            //free(info1);
            //free(info2);
        }
        i++;
        k--;
        ks1 = ks1->next;
        if (ks1 != NULL)
            item = ks1->item;
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

int getUnsInt(unsigned int *a){
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

#endif
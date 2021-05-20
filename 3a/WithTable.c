#include "Table.h"
#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef B
KeySpace1 ** FindLastSpaceone(Table *a, char *key, Item **item){
    KeySpace1 **ks1 = &a->ks1;
    int ver=1;
    do{
        if (*ks1 == NULL){
            *ks1 = (KeySpace1 *)malloc(sizeof(KeySpace1));
            (*ks1)->key1 = key;
            (*ks1)->ver = ver;
            (*ks1)->item = NULL;
            (*ks1)->next = NULL;
            if ((*item)->key1==NULL)
                (*item)->key1 = &a->ks1;
            break;
        }
        if (strcmp((*ks1)->key1, key)==0) {
            ver = (*ks1)->ver + 1;
        }
        (*item)->key1 = &(*ks1)->next;
        (ks1) = &(*ks1)->next;
    }while (1);
    return ks1;
}

KeySpace2 ** FindLastSpacetwo(Table *a, unsigned int key){
    KeySpace2 **ks2 = &a->ks2[hash(key)];
    do{
        if (*ks2 == NULL){
            *ks2 = (KeySpace2 *)calloc(1,sizeof(KeySpace2));
            (*ks2)->key2 = key;
            (*ks2)->node = NULL;
            (*ks2)->next = NULL;
            break;
        }
        if ((*ks2)->key2 == key)
            break;
        if ((*ks2)->key2 != key){
            ks2 = &(*ks2)->next;
        }
    }while(1);
    return ks2;
}

int EnterElement(Table *a, char *key1, unsigned int key2, char *inf1, char *inf2){
    if (CheckKeys(a, key1, key2)==0) {
        return 0;
    }
    Item *item = (Item *)calloc(1, sizeof(Item));
    item->info = (Info *)calloc(1, sizeof(Info));
    item->info->str1 = inf1;
    item->info->str2 = inf2;
    AddInSpace1(item, a, key1);
    AddInSpace2(item, a, key2);
    a->csize1 +=1;
    return 1;
}

int CheckKeys(Table *a, char *key1, unsigned int key2){
    KeySpace1 *ks1 = a->ks1;
    while(ks1!=NULL){
        if (strcmp(ks1->key1, key1)==0 && ks1->item->key2->key2 == key2)
            return 0;
        ks1 = ks1->next;
    }
    return 1;
}

void AddInSpace1(Item *item, Table *a, char *key1){
    KeySpace1 **ks1 = FindLastSpaceone(a, key1, &item);
    (*ks1)->item = item;
    (*ks1)->next = NULL;
}

int hash(unsigned int key){
    return (int) (key%msize2);
}

void AddInSpace2(Item *item, Table *a, unsigned int key2){
    KeySpace2 **ks2 = FindLastSpacetwo(a, key2);
    Node2 *node = (Node2 *)calloc(1, sizeof(Node2));
    node->ver2 = CheckVersion2(a, key2);
    item->key2 = *ks2;
    item->ver2 = node->ver2;
    node->item = item;
    node->next = NULL;
    (*ks2)->key2 = key2;
    node->next = (*ks2)->node;
    (*ks2)->node = node;
}

int CheckVersion2(Table *a, unsigned int key){
    KeySpace2 *ks2 = a->ks2[hash(key)];
    Node2 *node = NULL;
    int ver = 0;
    while(ks2!=NULL){
        if (ks2->key2 == key) {
            node = ks2->node;
            break;
        }
        ks2 = ks2->next;
    }
    if (node != NULL){
        ver = node->ver2;
    }
    return ver+1;
}

void TableInit(Table **table){
    if (*table == NULL){
        *table = (Table *)malloc(sizeof(Table));
        (*table)->ks1 = NULL;
        (*table)->ks2 = (KeySpace2 **)calloc(msize2, sizeof(KeySpace2));
        (*table)->csize1 = 0;
    }
}

void DeleteTable(Table *a){
    if (a==NULL){
        return;
    }
    if ((a)->csize1==0){
        free((a)->ks2);
        free(a);
        return;
    }
    KeySpace1 *ks1 = (a)->ks1;
    KeySpace2 **ks2 = (a)->ks2;
    while(ks1!=NULL){
        free(ks1->key1);
        free(ks1->item->info->str1);
        free(ks1->item->info->str2);
        free(ks1->item->info);
        KeySpace1 *kss1 = ks1;
        free(ks1->item);
        ks1 = ks1->next;
        free(kss1);
    }
    for (int i=0; i<msize2; i++) {
        while (ks2[i] != NULL) {
            KeySpace2 *kss2 = ks2[i];
            while (kss2->node != NULL) {
                Node2 *node = kss2->node;
                kss2->node = kss2->node->next;
                free(node);
            }
            ks2[i] = ks2[i]->next;
            free(kss2);
        }
    }
    free((a)->ks2);
    free(a);
    a = NULL;
}

void SearchSpace1Without(Table *a, char *key){
    KeySpace1 *ks1 = a->ks1;
    Table *b = NULL;
    TableInit(&b);
    while (ks1 != NULL){
        if (strcmp(ks1->key1, key)==0){
            int k1 =(int) strlen(ks1->item->info->str1)+1;
            int k2 = (int) strlen(ks1->item->info->str2)+1;
            char *inf1 = (char *)malloc(k1);
            char *inf2 = (char *)malloc(k2);
            int lenkey = (int) strlen(key)+1;
            char *key1 = (char *)malloc(lenkey);
            unsigned int key2 = ks1->item->key2->key2;
            memcpy(key1, key, lenkey);
            memcpy(inf1, ks1->item->info->str1, k1);
            memcpy(inf2, ks1->item->info->str2, k2);
            if (EnterElement(b, key1, key2,inf1 , inf2)==0){
                return;
            }
        }
        ks1 = ks1->next;
    }
    PrintTableConsole(b);
    DeleteTable(b);
}

void SearchSpace1WithVer(Table *a, char *key, unsigned int ver){
    KeySpace1 *ks1 = a->ks1;
    Table *b = NULL;
    TableInit(&b);
    while (ks1 != NULL){
        if (strcmp(ks1->key1, key)==0 && ks1->ver==ver){
            int k1 =(int) strlen(ks1->item->info->str1)+1;
            int k2 = (int) strlen(ks1->item->info->str2)+1;
            char *inf1 = (char *)malloc(k1);
            char *inf2 = (char *)malloc(k2);
            int lenkey = (int) strlen(key)+1;
            char *key1 = (char *)malloc(lenkey);
            unsigned int key2 = ks1->item->key2->key2;
            memcpy(key1, key, lenkey);
            memcpy(inf1, ks1->item->info->str1, k1);
            memcpy(inf2, ks1->item->info->str2, k2);
            if (EnterElement(b, key1, key2,inf1 , inf2)==0){
                return;
            }
            b->ks1->ver =(int) ver;
            break;
        }
        ks1 = ks1->next;
    }
    PrintTableConsole(b);
    DeleteTable(b);
}

void SearchSpace2Without(Table *a, unsigned int key){
    KeySpace2 *ks2 = a->ks2[hash(key)];
    Node2 *node = NULL;
    Table *b = NULL;
    TableInit(&b);
    while(ks2 != NULL){
        if (ks2->key2 == key){
            int i=0;
            node = ks2->node;
            while (node!=NULL) {
                int k1 = (int) strlen(node->item->info->str1) + 1;
                int k2 = (int) strlen(node->item->info->str2) + 1;
                char *inf1 = (char *) malloc(k1);
                char *inf2 = (char *) malloc(k2);
                memcpy(inf1, node->item->info->str1, k1);
                memcpy(inf2, node->item->info->str2, k2);
                char *key1 = NULL;
                int lenkey = (int) strlen((*node->item->key1)->key1) + 1;
                key1 = (char *) malloc(lenkey);
                memcpy(key1, (*node->item->key1)->key1, lenkey);
                if (EnterElement(b, key1, key,inf1 , inf2)==0){
                    return;
                }
                node = node->next;
            }
        }
        ks2 = ks2->next;
    }
    PrintTableConsole(b);
    DeleteTable(b);
}

void SearchSpace2WithVer(Table *a,unsigned int key, unsigned int ver){
    KeySpace2 *ks2 = a->ks2[hash(key)];
    Table *b = NULL;
    TableInit(&b);
    while(ks2 != NULL){
        if (ks2->key2 == key){
            break;
        }
        ks2 = ks2->next;
    }
    if (ks2==NULL){
        DeleteTable(b);
        return;
    }
    Node2 *node = ks2->node;
    while (node!=NULL) {
        if (node->ver2 == ver) {
            int k1 = (int) strlen(node->item->info->str1) + 1;
            int k2 = (int) strlen(node->item->info->str2) + 1;
            char *inf1 = (char *) malloc(k1);
            char *inf2 = (char *) malloc(k2);
            memcpy(inf1, node->item->info->str1, k1);
            memcpy(inf2, node->item->info->str2, k2);
            char *key1 = NULL;
            int lenkey = (int) strlen((*node->item->key1)->key1) + 1;
            key1 = (char *) malloc(lenkey);
            memcpy(key1, (*node->item->key1)->key1, lenkey);
            if (EnterElement(b, key1, key, inf1, inf2) == 0) {
                return;
            }
            b->ks2[hash(key)]->node->ver2 = (int) ver;
            b->ks1->item->key2->node->ver2 = (int) ver;
        }
        node = node->next;
    }
    PrintTableConsole(b);
    DeleteTable(b);
}

int DeleteElementsBySpace1(Table *a, char *key){
    KeySpace1 *ks1 = (a)->ks1;
    KeySpace2 *ks2 = NULL;
    KeySpace2 *kks2 = NULL;
    KeySpace1 *kks1 = NULL;
    while (ks1 != NULL) {
        if (strcmp(ks1->key1, key)==0){
            unsigned int key2 = ks1->item->key2->key2;
            ks2 = a->ks2[hash(key2)];
            while (ks2->key2!=key2){
                kks2 = ks2;
                ks2 = ks2->next;
            }
            Node2 *node = ks2->node;
            Node2 *cnode = NULL;
            while (strcmp((*node->item->key1)->key1, key)!=0) {
                printf("ok\n");
                cnode = node;
                node = node->next;
            }
            free(ks1->key1);ks1->key1=NULL;
            free(ks1->item->info->str1); ks1->item->info->str1=NULL;
            free(ks1->item->info->str2); ks1->item->info->str2=NULL;
            free(ks1->item->info); ks1->item->info=NULL;
            KeySpace1 *kss1 = ks1;
            free(ks1->item);ks1->item=NULL;
            if (kks1==NULL){
                a->ks1 = ks1->next;
            }else {
                kks1->next = ks1->next;
            }
            ks1 = ks1->next;
            free(kss1);kss1=NULL;
            if (cnode == NULL && node->next==NULL){
                if (kks2==NULL){
                    a->ks2[hash(key2)] = ks2->next;
                }else {
                    kks2->next = ks2->next;
                }
                free(node); node = NULL;
                free(ks2);ks2 = NULL;
            } else {
                if (cnode == NULL){
                    free(node); node = NULL;
                }else {
                    cnode->next = node->next;
                    free(node);
                    node = NULL;
                }
            }
            a->csize1-=1;
        }else {
            kks1 = ks1;
            ks1 = ks1->next;
        }
    }
    PrintTableConsole(a);
    return 1;
}

int DeleteElementVerBySpace1(Table *a, char *key, unsigned int ver){
    KeySpace1 *ks1 = (a)->ks1;
    KeySpace2 *ks2 = NULL;
    KeySpace2 *kks2 = NULL;
    KeySpace1 *kks1 = NULL;
    while (ks1 != NULL) {
        if (strcmp(ks1->key1, key)==0 && ks1->ver == ver){
            unsigned int key2 = ks1->item->key2->key2;
            ks2 = a->ks2[hash(key2)];
            while (ks2->key2!=key2){
                kks2 = ks2;
                ks2 = ks2->next;
            }
            Node2 *node = ks2->node;
            Node2 *cnode = NULL;
            while (strcmp((*ks2->node->item->key1)->key1, key)!=0 && (*ks2->node->item->key1)->ver != ver) {
                cnode = node;
                node = node->next;
            }
            free(ks1->key1);
            ks1->key1=NULL;
            free(ks1->item->info->str1); ks1->item->info->str1=NULL;
            free(ks1->item->info->str2); ks1->item->info->str2=NULL;
            free(ks1->item->info); ks1->item->info=NULL;
            KeySpace1 *kss1 = ks1;
            free(ks1->item);ks1->item=NULL;
            if (kks1==NULL){
                a->ks1 = ks1->next;
            }else {
                kks1->next = ks1->next;
            }
            ks1 = ks1->next;
            free(kss1);kss1=NULL;
            if (cnode == NULL && node->next==NULL){
                if (kks2==NULL){
                    a->ks2[hash(key2)] = ks2->next;
                }else {
                    kks2->next = ks2->next;
                }
                free(node); node = NULL;
                free(ks2);ks2 = NULL;
            } else {
                cnode->next = node->next;
                free(node); node = NULL;
            }
            a->csize1--;
        }else{
            kks1 = ks1;
            ks1 = ks1->next;
        }
    }
    PrintTableConsole(a);
    return 1;
}

int SearchElementByTwoKey(Table *a, char *key1, unsigned int key2){
    KeySpace2 *ks2 = a->ks2[hash(key2)];
    while (ks2!=NULL && ks2->key2!=key2){
        ks2 = ks2->next;
    }
    if (ks2 == NULL) {
        return 0;
    }
    Node2 *node = ks2->node;
    while (node != NULL){
        if (strcmp((*node->item->key1)->key1, key1)==0 && ks2->key2==key2){
            printf("Searched Element:\n");
            printf("    Key 1: %s", (*node->item->key1)->key1);
            printf("    Key 1 version: %d\n", (*node->item->key1)->ver);
            printf("    Key 2: %u", ks2->key2);
            printf("    Key 2 version: %d\n",node->ver2);
            printf("    Value:\n    1 string: %s\n    2 string: %s\n", node->item->info->str1, node->item->info->str2);
            return 1;
        }
        node = node->next;
    }
}

int DeleteElementsBySpace2(Table *a, unsigned int key){
    KeySpace2 *ks2 = a->ks2[hash(key)];
    if (ks2==NULL){
        return 0;
    }
    while ((ks2)->key2!=key && ks2 != NULL){
        ks2 = (ks2)->next;
    }
    printf("%p\n", ks2);
    if (ks2==NULL){
        return 0;
    }
    else {
        Node2 *node = (ks2)->node->next;
        Node2 *cnode = ks2->node;
        printf("%d\n", cnode->item->ver2);
        while (cnode->next != NULL){
            free(node->item->info->str1); node->item->info->str1=NULL;
            free(node->item->info->str2);node->item->info->str2 = NULL;
            free(node->item->info); node->item->info = NULL;
            KeySpace1 **ks1 = (node->item->key1); //отвечает за элемент, который нужно удалить
            KeySpace1 *kks1 = (*node->item->key1)->next; //
            free((*ks1)->key1); (*ks1)->key1 = NULL;
            free((*ks1)->item); (*ks1)->item = NULL;
            free(*ks1);
            *ks1 = kks1;
            if (node->next == NULL){
                cnode->next = NULL;
            } else {
                cnode->next = node->next;
            }
            Node2 *pnode = node;

            node = node->next;
            free(pnode);
            pnode = NULL;
            a->csize1--;
        }
    }
    return 1;
}

int DeleteByTwoKeys(Table *a, char *key1, unsigned int key2){
    KeySpace2 *ks2 = a->ks2[hash(key2)];
    KeySpace2 *kks2 = NULL;
    while (ks2!=NULL && ks2->key2!=key2){
        kks2 = ks2;
        ks2 = ks2->next;
    }
    if (ks2==NULL){
        return 0;
    } else {
        Node2 *node = (ks2)->node;
        Node2 *cnode = NULL;
        while (node != NULL && strcmp((*node->item->key1)->key1, key1)!=0) {
            cnode = node;
            node = node->next;
        }
        if(node == NULL){
            return 0;
        }
        printf("%s\n", (*node->item->key1)->key1);
        free(node->item->info->str1);
        free(node->item->info->str2);
        free(node->item->info);
        KeySpace1 **ks1 = node->item->key1;
        KeySpace1 *kks1 = (*node->item->key1)->next;
        free((*ks1)->key1);
        free((*ks1)->item);
        if (*ks1 == a->ks1){
            free(*ks1);
            a->ks1 = kks1;
            if (kks1!=NULL)
                kks1->item->key1 = &a->ks1;
        } else {
            free(*ks1);
            *ks1 = kks1;
            if (kks1!=NULL)
                kks1->item->key1 = &(*ks1);
        }
        if (node->next==NULL) {
            if (cnode == NULL) {
                ks2->node = node->next;
            } else {
                cnode->next = node->next;
            }
            if (kks2!=NULL) {
                kks2->next = ks2->next;
            } else {
                a->ks2[hash(key2)] = ks2->next;
            }
            free(node);
            free(ks2);
        } else {
            if (cnode == NULL) {
                ks2->node = node->next;
            } else {
                cnode->next = node->next;
            }
            free(node);
            node = NULL;
        }

        a->csize1--;
    }
    return 1;
}
#endif
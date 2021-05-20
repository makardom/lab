#include "Tree.h"
#include "Functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void TreeInit(Tree **a){
    *a = (Tree *) malloc(sizeof(Tree));
    (*a)->size = 0;
    (*a)->node = NULL;
}

void NodeInit(Item **elem){
    *elem = (Item *) malloc(sizeof(Item));
    (*elem)->right=NULL;
    (*elem)->left = NULL;
    (*elem)->key = (char *) calloc(N, sizeof(char));
    (*elem)->info = NULL;
}

void AddInTree(Item *node, Item *add, char *key){
    if (strcmp(node->key, key)>0 && node->left!=NULL)
        AddInTree(node->left, add, key);
    else if (strcmp(node->key, key)>0){
        node->left = add;
    }else if (strcmp(node->key, key)<0 && node->right!=NULL){
        AddInTree(node->right, add, key);
    }else if (strcmp(node->key, key)<0){
        node->right = add;
    }else if (strcmp(node->key, key)==0 && node->left!=NULL){
        if (strcmp(node->left->key, key)==0){
            AddInTree(node->left, add, key);
        }else {
            add->ver = node->ver + 1;
            add->left = node->left;
            node->left = add;
        }
    }
    else if (strcmp(node->key, key)==0 && node->right!=NULL){
        if (strcmp(node->right->key, key)==0){
            AddInTree(node->right, add, key);
        }else {
            add->ver = node->ver + 1;
            add->right = node->right;
            node->right = add;
        }
    } else {
        add->ver = node->ver +1;
        node->left = add;
    }
}

void AddNodeInTree(Tree *a, Info *info, char *key){
    Item *add;
    NodeInit(&add);
    add->info = info;
    add->ver = 1;
    strcpy(add->key, key);
    if (a->node==NULL){
        a->node = add;
        a->size=1;
        return;
    }
    Item *element = a->node;
    AddInTree(element, add, key);
}

int SearchElement(Tree *a, char *key, int ver){
    Item *node = a->node;
    while (node!=NULL){
        if (strcmp(node->key, key)==0){
            if (ver==node->ver) {
                PrintElement(node);
                return 1;
            }
            else{
                if (node->right!=NULL) {
                    if (strcmp(node->right->key, key) == 0) {
                        node = node->right;
                    } else {
                        return 0;
                    }
                }else if (node->left!=NULL) {
                    if (strcmp(node->left->key, key)==0) {
                        node = node->left;
                    } else {
                        return 0;
                    }
                }else {
                    return 0;
                }
            }
        }
        else if (strcmp(node->key, key)>0){
            node = node->left;
        }
        else {
            node = node->right;
        }
    }
    return 0;
}

void DeleteNodes(Item *node){
    if (node != NULL){
        DeleteNodes(node->left);
        DeleteNodes(node->right);
        free(node->key);
        free(node->info->str);
        free(node->info);
        free(node);
    }
}

void DeleteTree(Tree **a){
    if (*a!=NULL){
        DeleteNodes((*a)->node);
        free(*a);
    }
}

void DeleteNode(Item *node){
    free(node->key);
    free(node->info->str);
    free(node->info);
    free(node);
}

void FindMaxLeft(Item *node, Item *pered, int nap, Tree *a){
    Item *cnode = node->left;
    Item *prenode = NULL;
    while (cnode->right!=NULL){
        prenode = cnode;
        cnode = cnode->right;
    }
    if (prenode==NULL){
        cnode->right = node->right;
        DeleteNode(node);
        if (pered == NULL){
            a->node = cnode;
        }else if (nap==1){
            pered->right = cnode;
        }else if (nap==-1){
            pered->left = cnode;
        }
    } else {
        prenode->right = cnode->left;
        cnode->left = node->left;
        cnode->right = node->right;
        DeleteNode(node);
        if (pered == NULL) {
            a->node = cnode;
        } else if (nap == 1) {
            pered->right = cnode;
        } else if (nap == -1) {
            pered->left = cnode;
        }
    }
}

void FindMinRight(Item *node, Item *pered, int nap, Tree *a){
    Item *cnode = node->right;
    Item *prenode = NULL;
    while (cnode->left!=NULL){
        prenode = cnode;
        cnode = cnode->left;
    }
    printf("nap: %d\n", nap);
    if (prenode==NULL){
        cnode->left = node->left;
        DeleteNode(node);
        if (pered == NULL){
            a->node = cnode;
        }else if (nap==1){
            pered->right = cnode;
        }else if (nap==-1){
            pered->left = cnode;
        }
    } else {
        prenode->left = cnode->right;
        cnode->left = node->left;
        cnode->right = node->right;
        DeleteNode(node);
        if (pered == NULL) {
            a->node = cnode;
        } else if (nap == 1) {
            pered->right = cnode;
        } else if (nap == -1) {
            pered->left = cnode;
        }
    }
}

int DeleteElement(Tree *a, char *key, int ver){
    Item *node = (a)->node;
    Item *prenode = NULL;
    int nap;
    while (node != NULL) {
        if (strcmp(node->key, key)==0 && node->ver==ver){ //добавить версию
            if (node->left==NULL && node->right==NULL){
                DeleteNode(node);
                if (prenode==NULL){
                    a->node = NULL;
                }else if (nap==1){
                    prenode->right = NULL;
                } else if (nap == -1){
                    prenode->left = NULL;
                }
                return 0;
            }else if (node->left==NULL){
                FindMinRight(node, prenode, nap, a);
                return 0;
            } else if (node->right==NULL){
                FindMaxLeft(node, prenode, nap, a);
                return 0;
            } else {
                FindMaxLeft(node, prenode, nap, a);
                return 0;
            }
        }else if (strcmp(node->key, key)==0){
            if (node->left==NULL && node->right==NULL){
                return 1;
            }
            else if (node->left!=NULL) {
                if (strcmp(node->left->key, key) == 0) {
                    prenode = node;
                    node = node->left;
                    nap = -1;
                }
            } else if (node->right!=NULL) {
                if (strcmp(node->right->key, key) == 0){
                    prenode = node;
                    node = node->right;
                    nap = 1;
                }
            }else
                return 1;
        }
        else if (strcmp(node->key, key)>0){
            prenode = node;
            node = node->left;
            nap = -1;
        } else if (strcmp(node->key, key)<0){
            prenode = node;
            node = node->right;
            nap = 1;
        }
    }
    return 1;
}

int LoadTree(FILE *fp, Tree *a){
    char *key = NULL;
    char *inf = NULL;
    float c,b;
    fseek(fp, 0, SEEK_SET);
    while((key = readStringFile(fp))!=NULL){
        if (strlen(key)+1>N){
            return 1;
        }
        int pos = ftell(fp);
        fscanf(fp, "%f", &c);
        fscanf(fp, "%f", &b);
        inf = readStringFile(fp);
        Info *info = (Info *) malloc(sizeof(Info));
        info->num1 = c;
        info->num2 = b;
        info->str = inf;
        AddNodeInTree(a, info, key);
    }
}

void SaveInFile(FILE *fp, Item *node){
    if (node!=NULL){
        fprintf(fp, "%s\n%f %f %s\n", node->key, node->info->num1, node->info->num2, node->info->str);
        SaveInFile(fp, node->left);
        SaveInFile(fp, node->right);
    }
}

char *RandomString(int k){
    int kol = rand()%(N-1)+1;
    char *res = (char *) malloc(kol);
    for (int i=0; i<kol-1; ++i){
        res[i]=(char)(65+rand()%58);
    }
    res[kol-1]='\0';
    return res;
}

void D_Timing(){
    FILE *fp;
    printf("Enter file's name:");
    char *name;
    if ((name=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    if ((fp = fopen (name, "w"))==NULL){
        free(name);
        printf("File cannot be opened\n");
        return;
    }
    clock_t start, end;
    double s_add, s_del, s_ser;
    int kol[] = {50, 100, 200, 400, 800, 1600};
    fprintf(fp, "x;y\n");
        start = clock();
    srand(time(NULL));
        for (int i=1000; i<10000; i+=1000) {
            s_add=0; s_del=0; s_ser=0;
            Timing(&s_add, &s_del, &s_ser, i);
            s_ser = (double)((s_ser/CLOCKS_PER_SEC)/(i*5));
            fprintf(fp, "%d; %0.8lf\n", i, s_ser);
        }
    for (int i=10000; i<110000; i+=10000) {
        s_add=0; s_del=0; s_ser=0;
        Timing(&s_add, &s_del, &s_ser, i);
        s_ser = (double)((s_ser/CLOCKS_PER_SEC)/(i*5));
        fprintf(fp, "%d; %0.8lf\n", i, s_ser);
    }
        end = clock();
        double all;
        all = (double) ((double) (end - start) / CLOCKS_PER_SEC);
        printf("Time to all: %0.6lf\n", all);
    fclose(fp);
}

void Timing(double *add, double *del, double *ser, int n){
    Tree *a=NULL;
    clock_t start_add, stop_add, start_del, stop_del, start_ser, stop_ser;
    double time_add = 0;
    for (int j=0; j<5; j++) {
        TreeInit(&a);
        for (int i = 0; i < n; ++i) {
            char *key = RandomString(rand());
            float num1, num2;
            num1 = rand();
            num2 = rand();
            char *str = RandomString(rand());
            Info *info = (Info *) malloc(sizeof(Info));
            info->str = str;
            info->num1 = num1;
            info->num2 = num2;
            start_add = clock();
            AddNodeInTree(a, info, key);
            stop_add = clock();
            time_add += (double) ((double) (stop_add - start_add) / CLOCKS_PER_SEC);
        }
        int kol = 0;
        *add += time_add;
        for (int i = 0; i < n; ++i) {
            char *key = RandomString(rand());
            int ver = (int) rand();
            start_ser = clock();
            if (SearchElement(a, key, ver) == 0) {
                printf("Element not found\n");
            }
            stop_ser = clock();
            *ser += (stop_ser - start_ser);
        }
        DeleteTree(&a);
    }
}
#include "RBTree.h"
#include "Functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

Node *rotateRight(Node *h, Node *Elist){
    Node *x = h->left;
    int color = x->color;
    h->left = x->right;
    if (x->right!=Elist){
        x->right->parent = h;
    }
    x->right = h;
    x->color = h->color;
    x->parent = h->parent;
    h->parent = x;
    h->color = color;
    return x;
}

Node *rotateLeft(Node *h, Node *Elist){
    Node *x = h->right;
    int color = x->color;
    h->right = x->left;
    if (x->left!=Elist){
        x->left->parent = h;
    }
    x->left = h;
    x->color = h->color;
    x->parent = h->parent;
    h->parent = x;
    h->color = color;
    return x;
}

void ColorFlip(Node *node){
    int color = node->color;
    node->color = node->left->color;
    node->left->color = color;
    node->right->color = color;
}

void TreeInit(Tree **a, Node *Elist){
    *a = (Tree *) malloc(sizeof(Tree));
    (*a)->size = 0;
    (*a)->node = Elist;
}

void NodeInit(Node **elem, Node *Elist){
    *elem = (Node *) malloc(sizeof(Node));
    (*elem)->right=Elist;
    (*elem)->left = Elist;
    (*elem)->parent = Elist;
    (*elem)->key =(char *) malloc(sizeof(char));
    (*elem)->info = NULL;
    (*elem)->color = RED;
}

Node *insert(Node *node, Node *x, Node *Elist, int ver){
    if (node == Elist){
        x->ver = ver;
        return x;
    }
    if (strcmp(node->key, x->key)==0 && ver<=node->ver)
        ver = node->ver+1;
    if (strcmp(node->key, x->key)>=0){
        node->left = insert(node->left, x, Elist, ver);
    }else{
        node->right = insert(node->right, x, Elist, ver);
    }
    if (node->right->color==RED && node->left->color==BLACK) {
        node = rotateLeft(node, Elist);
    }
    if (node->left->color==RED && node->left->left->color==RED) {
        node = rotateRight(node, Elist);
    }
    if (node->left->color==RED && node->right->color==RED){
        ColorFlip(node);
    }
    return node;
}

void AddInTree2(Tree *a, Node *add, Node *Elist, int ver){
    a->node = insert(a->node, add, Elist, ver);
    a->node->color = BLACK;
}

void FixRightRed(Tree *a, Node *x, Node *Elist){
    if (x!=Elist){
        if (x->right->color==RED){
                Left_Rotate(a, x, Elist);
                x->color = RED;
                x->parent->color = BLACK;
            FixRightRed(a, x->parent, Elist);
        }
        if (x->left->color==RED && x->left->left->color==RED){
                Right_Rotate(a, x, Elist);
                FixRightRed(a, x->parent, Elist);
        }
        if (x->left->color==RED && x->right->color==RED){
            x->color = RED;
            x->left->color = BLACK;
            x->right->color = BLACK;
            FixRightRed(a, x->parent, Elist);
        }
        FixRightRed(a, x->right, Elist);
        FixRightRed(a, x->left, Elist);
    }
}

void AddNodeInTree(Tree *a, Info *info, char *key, Node *Elist){
    Node *add;
    NodeInit(&add, Elist);
    add->info = info;
    add->ver = 1;
    add->color = RED;
    add->parent = Elist;
    strcpy(add->key, key);
    if (a->node==Elist){
        add->color = 0;
        a->node = add;
        a->size=1;
        return;
    }
    Node *element = a->node;
    int ver = 1;
    a->size++;
    AddInTree2(a, add, Elist, ver);
    //FixRightRed(a, a->node, Elist);
    //SecondStepToAdd(a, add, Elist);
    //FixRightRed(a, a->node, Elist);
}

void SecondStepToAdd(Tree *a, Node *x, Node *Elist){
    while (x->parent->color==RED) {
        Node *p1 = x->parent;
        Node *pp = p1->parent;
        if (p1 == pp->left){
            Node *p2 = pp->right;
            if (p2->color==RED){
                p1->color=BLACK;
                pp->color=RED;
                p2->color=BLACK;
                x = pp;
                if (x->parent==Elist){
                    x->color = BLACK;
                    return;
                }
                continue;
            }
            else if (x==p1->right){
                x=p1;
                Left_Rotate(a, x, Elist);
                p1 = x->parent;
                pp = p1->parent;
            }
            p1->color = BLACK;
            pp->color = RED;
            Right_Rotate(a, pp, Elist);

        } else {
            Node *p2 = pp->left;
            if (p2->color==RED){
                p1->color=BLACK;
                pp->color=RED;
                p2->color=BLACK;
                x = pp;
                if (x->parent==Elist){
                    x->color = BLACK;
                    return;
                }
                continue;
            }
            else if (x==p1->left){
                x=p1;
                Right_Rotate(a, x, Elist);
                p1 = x->parent;
                pp = p1->parent;
            }
            p1->color = BLACK;
            pp->color = RED;
            Left_Rotate(a, pp, Elist);

        }
    }
    a->node->color = BLACK;
}

void Left_Rotate(Tree *a, Node *x, Node *EList){
    Node *y, *p;
    y=x->right;
    p=x->parent;
    x->right = y->left;
    if (y->left!=EList){
        y->left->parent = x;
    }
    y->parent = p;
    if (p==EList){
        a->node = y;
    } else {
        if (p->left==x){
            p->left=y;
        } else{
            p->right=y;
        }
    }
    y->left = x;
    x->parent = y;
}

void Right_Rotate(Tree *a, Node *x, Node *EList){
    Node *y, *p;
    y=x->left;
    p=x->parent;
    x->left = y->right;
    if (y->right!=EList){
        y->right->parent = x;
    }
    y->parent = p;
    if (p==EList){
        a->node = y;
    } else {
        if (p->left==x){
            p->left=y;
        } else{
            p->right=y;
        }
    }
    y->right = x;
    x->parent = y;
}

int SearchElement(Tree *a, char *key, int ver, Node *Elist){
    Node *node = a->node;
    while (node!=Elist){
        if (strcmp(node->key, key)>=0){
            if (strcmp(node->key, key)==0){
                if (node->ver==ver){
                    PrintElement(node);
                    return 0;
                } else if (node->ver>ver){
                    node = node->right;
                } else {
                    node = node->left;
                }
            } else {
                node = node->left;
            }
        }
        else {
            node = node->right;
        }
    }
    return 1;
}

int NewSearchElement(Tree *a, char *key, int ver, Node *Elist){
    Node *node = a->node;
    while (node!=Elist){
        if (strcmp(node->key, key)>=0){
            if (strcmp(node->key, key)==0){
                if (node->ver==ver){
                    return 0;
                } else if (node->ver>ver){
                    node = node->right;
                } else {
                    node = node->left;
                }
            } else {
                node = node->left;
            }
        }
        else {
            node = node->right;
        }
    }
    return 1;
}

int LoadTree(FILE *fp, Tree *a, Node *Elist){
    char *key = NULL;
    char *inf = NULL;
    float c,b;
    fseek(fp, 0, SEEK_SET);
    while((key = readStringFile(fp))!=NULL){
        int pos = ftell(fp);
        fscanf(fp, "%f", &c);
        fscanf(fp, "%f", &b);
        inf = readStringFile(fp);
        Info *info = (Info *) malloc(sizeof(Info));
        info->num1 = c;
        info->num2 = b;
        info->str = inf;
        AddNodeInTree(a, info, key, Elist);
    }
}

void SaveInFile(FILE *fp, Node *node, Node *Elist){
    if (node!=Elist){
        fprintf(fp, "%s\n%f %f %s\n", node->key, node->info->num1, node->info->num2, node->info->str);
        SaveInFile(fp, node->left, Elist);
        SaveInFile(fp, node->right, Elist);
    }
}

void DeleteNodes(Node *node, Node *Elist){
    if (node != Elist){
        DeleteNodes(node->left, Elist);
        DeleteNodes(node->right, Elist);
        free(node->key);
        free(node->info->str);
        free(node->info);
        free(node);
    }
}

void DeleteTree(Tree **a, Node *Elist){
    if (*a!=NULL){
        DeleteNodes((*a)->node, Elist);
        free(*a);
    }
}

Node *FindNode (Node *x, Node *Elist){
    Node *need;
    if (x->right!=Elist)
        x = x->right;
    else return x;
    while (x->left!=Elist){
        x = x->left;
    }
    need = x;
    return need;
}

Node *moveRedLeft(Node *node, Node *Elist){
    ColorFlip(node);
    if (node->right->left->color==RED){
        node->right = rotateRight(node->right, Elist);
        node = rotateLeft(node, Elist);
        ColorFlip(node);
    }
    return node;
}

Node *moveRedRight(Node *node, Node *EList){
    ColorFlip(node);
    if (node->left->left->color==RED){
        node = rotateRight(node, EList);
        ColorFlip(node);
    }
    return node;
}

Node *FixUp(Node *node, Node *Elist){
    if (node->right->color==RED && node->left->color==BLACK)
        node = rotateLeft(node, Elist);
    if (node->left->color==RED && node->left->left->color==RED)
        node = rotateRight(node, Elist);
    if (node->left->color==RED && node->right->color==RED)
        ColorFlip(node);
    return node;
}

Node *MinDelete(Node *node, Node *Elist){
    if (node->left == Elist)
        return Elist;
    if (node->left->color==BLACK && node->left->left->color==BLACK)
        node = moveRedLeft(node, Elist);
    node->left = MinDelete(node->left, Elist);
    return FixUp(node, Elist);
}

Node *Delete(Node *node, char *key, int ver, Node *Elist){
    if (strcmp(node->key, key)>0){
        if (node->left->color==BLACK && node->left->left->color==BLACK)
            node = moveRedLeft(node, Elist);
        node->left = Delete(node->left, key, ver, Elist);
    }
    else {
        if (node->left->color==RED)
            node = rotateRight(node, Elist);
        if (strcmp(node->key, key)==0 && node->right==Elist)
            return Elist;
        if (node->right->color==BLACK && node->right->left->color==BLACK)
            node = moveRedRight(node, Elist);
        if (strcmp(node->key, key)==0){
            if (node->ver==ver) {
                Node *moved = FindNode(node, Elist);
                node->key = moved->key;
                node->info = moved->info;
                node->ver = moved->ver;
                node->right = MinDelete(node->right, Elist);
            }else if (node->ver>ver){
                node->right = Delete(node->right, key, ver, Elist);
            }else {
                node->left = Delete(node->left, key, ver, Elist);
            }
        }
        else node->right = Delete(node->right, key, ver, Elist);
    }
    return FixUp(node, Elist);
}

int DeleteNode (Tree *a, char *key, int ver, Node *Elist){
    if (NewSearchElement(a, key, ver, Elist)==1)
        return 1;
    if (a->node->left->color==BLACK && a->node->right->color==BLACK)
        a->node->color=RED;
    a->node = Delete(a->node, key, ver, Elist);
    a->node->color = BLACK;
    a->size--;
    return 0;
}

/*void RB_Delete_Fixup(Tree *a, Node *x, Node *Elist){
    Node *p, *w;
    while (x!=a->node && x->color==BLACK){
        p = x->parent;
        if (x==p->left){
            w = p->right;
            if (w->color==RED){
                w->color = BLACK;
                p->color = RED;
                Left_Rotate(a, p, Elist);
                w = p->right;
            }
            if (w->left->color==BLACK && w->right->color==BLACK){
                w->color = RED;
                x = p;
            }
            else {
                if (w->right->color == BLACK) {
                    w->color = RED;
                    w->left->color = BLACK;
                    Right_Rotate(a, w, Elist);
                    w = p->right;
                }
                    w->color = p->color;
                    p->color = BLACK;
                    w->right->color = BLACK;
                    Left_Rotate(a, p, Elist);
                    x = a->node;

            }
        } else if (x==p->right) {
            w = p->left;
            if (w->color == RED) {
                w->color = BLACK;
                p->color = RED;
                Right_Rotate(a, p, Elist);
                w = p->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = p;
            } else {
                if (w->left->color == BLACK) {
                    w->color = RED;
                    w->right->color = BLACK;
                    Left_Rotate(a, w, Elist);
                    w = p->left;
                }
                w->color = p->color;
                p->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(a, p, Elist);
                x = a->node;
            }
        }
    }
    x->color=BLACK;
}

int DeleteElement(Tree *a, char *key, int ver, Node *Elist){
    Node *node = a->node;
    while (node != Elist){
        if (strcmp(node->key, key)==0){
            if (node->ver==ver){
                Node *y, *p;
                if (node->left==Elist || node->right==Elist){
                    y = node;
                }else{
                    y = FindNode(node, Elist);
                }
                if (y->left!=Elist){
                    p = y->left;
                } else {
                    p = y->right;
                }
                p->parent = y->parent;
                if (y->parent==Elist){
                    a->node = p;
                }
                else{
                    if (y->parent->left==y)
                        y->parent->left = p;
                    else
                        y->parent->right = p;
                }
                if (y!=node){
                    node->key = y->key;
                    node->ver = y->ver;
                    node->info = y->info;
                }
                PrintfTree(a->node, 0, Elist);
                if (y->color==BLACK){
                    RB_Delete_Fixup(a, p, Elist);
                }
                if (node->parent==Elist){
                    a->node->color=BLACK;
                }
                FixRightRed(a, a->node, Elist);
                return 0;
            }else{
                if (node->left==Elist && node->right==Elist) {return 1;}
                else if (node->ver>ver){

                    node = node->right;

                }else if (node->ver<ver){

                    node = node->left;

                }else {return 1;}
            }
        }
        else if (strcmp(node->key, key)>0){
            node = node->left;
        }
        else if (strcmp(node->key, key)<0){
            node = node->right;
        }
    }
    return 1;
}
*/
char *RandomString(){
    int kol = rand()%100+1;
    char *res = (char *) malloc(kol);
    for (int i=0; i<kol-1; ++i){
        res[i]=(char)(65+rand()%58);
    }
    res[kol-1]='\0';
    return res;
}

void D_Timing(Node *Elist){
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
        Timing(&s_add, &s_del, &s_ser, i, Elist);
        s_ser = (double)((s_ser/CLOCKS_PER_SEC)/(i*5));
        fprintf(fp, "%d; %0.8lf\n", i, s_ser);
    }
    for (int i=10000; i<110000; i+=10000) {
        s_add=0; s_del=0; s_ser=0;
        Timing(&s_add, &s_del, &s_ser, i, Elist);
        s_ser = (double)((s_ser/CLOCKS_PER_SEC)/(i*5));
        fprintf(fp, "%d; %0.8lf\n", i, s_ser);
    }
    end = clock();
    double all;
    all = (double) ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time to all: %0.6lf\n", all);
    fclose(fp);
}

void Timing(double *add, double *del, double *ser, int n, Node *Elist){
    Tree *a=NULL;
    clock_t start_ser, stop_ser;
    double time_add = 0;
    for (int j=0; j<5; j++) {
        TreeInit(&a, Elist);
        for (int i = 0; i < n; ++i) {
            char *key = RandomString();
            float num1, num2;
            num1 = rand();
            num2 = rand();
            char *str = RandomString();
            Info *info = (Info *) malloc(sizeof(Info));
            info->str = str;
            info->num1 = num1;
            info->num2 = num2;
            AddNodeInTree(a, info, key, Elist);
        }
        int kol = 0;
        *add += time_add;
        for (int i = 0; i < n; ++i) {
            char *key = RandomString(rand());
            int ver = (int) rand();
            start_ser = clock();
            if (SearchElement(a, key, ver, Elist) == 0) {
                printf("Element not found\n");
            }
            stop_ser = clock();
            *ser += (stop_ser - start_ser);
        }
        DeleteTree(&a, Elist);
    }
}


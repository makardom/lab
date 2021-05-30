#include "Graph.h"
#include "D_Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WHITE 0
#define HIGH 2147483647
#define BLACK 2

void InitNode(Node *a){
    a = (Node *) calloc(1, sizeof(Node));
    a->edges = NULL;
}

void GraphDelete(Graph *a){
    int i = a->kol;
    Element *elem;
    while (i!=0){
        elem = a->nodes;
        Node *node = elem->node;
        DeleteNodeInGraph(a, node->name);
        //elem = elem->next;
        i--;
    }
}

void InitGraph(Graph **a){
    (*a) = (Graph *) malloc(sizeof (Graph));
    (*a)->nodes = (Element *) malloc(sizeof (Element));
    (*a)->nodes->node = NULL;
    (*a)->nodes->next = NULL;
    (*a)->nodes=NULL;
    (*a)->kol = 0;
}

int AddNodeInGraph(Graph *a, Node *add){
    int i = 0;
    if (a->nodes==NULL){
        a->nodes = (Element *) calloc(1, sizeof(Element));
    }
    Element *node = (a->nodes);
    while (node != NULL && (node)->node!= NULL){
        if ((node)->node->x==add->x && (node)->node->y==add->y)
            return 1;
        i=node->node->name+1;
        node = (node)->next;
    }
    add->name = i;
    add->edges = NULL;
    Element *new = (Element *) malloc(sizeof(Element));
    new->node = add;
    new->next = NULL;
    a->kol ++;
    if (a->kol==1){
        a->nodes = new;
        return 0;
    }
    node = a->nodes;
    while (node->next!=NULL){
        node = node->next;
    }
    (node)->next = new;
}

Node *FindNodeByName(Graph *a, int name){
    Element *elem = a->nodes;
    while (elem != NULL){
        if (elem->node->name == name){
            break;
        }
        elem = elem->next;
    }
    if (elem == NULL){
        return NULL;
    }
    return elem->node;
}

int AddEdgeInGraph(Graph *a, int name1, int name2){
    Element *elem = a->nodes;
    while (elem != NULL){
        if (elem->node->name==name1){
            break;
        }
        elem = elem->next;
    }
    if (elem == NULL){
        return 1;
    }
    Edge *edge = (Edge *) malloc(sizeof(Edge));
    edge->next = NULL;
    if ((edge->node= FindNodeByName(a, name2))==NULL){
        return 2;
    }
    Node *node = elem->node;
    Edge *edge1 = (Edge *) malloc(sizeof(Edge));
    edge1 = node->edges;
//    while (edge1!=NULL){
//        if (edge1->node->name==name2)
//            return 3;
//        edge1 = edge1->next;
//    }
    node = elem->node;
//    edge1 = node->edges;
    if (edge1==NULL){
        node->edges = edge;
        return 0;
    }
    while (edge1->next != NULL){
        edge1 = edge1->next;
    }
     edge1->next = edge;
    return 0;
}

int DeleteEdgeInGraph(Graph *a, int name1, int name2){
    Element *elem = a->nodes;
    while (elem != NULL){
        if (elem->node->name==name1){
            break;
        }
        elem = elem->next;
    }
    if (elem == NULL){
        return 1;
    }
    Node *node = elem->node;
    Edge *edge = node->edges;
    Edge *preedge = NULL;
    if (edge==NULL){
        return 2;
    }
    if (edge->node->name == name2){
        node->edges = edge->next;
        free(edge);
        return 0;
    }
    while(edge!=NULL){
        if (edge->node->name==name2){
            preedge->next = edge->next;
            free(edge);
            return 0;
        }
        preedge = edge;
        edge = edge->next;
    }
    if (edge==NULL){
        return 2;
    }
}

void DeleteEdges(Graph *a, int name){
    Element *elem = a->nodes;
    while (elem!=NULL){
        Node *node = elem->node;
        Edge *edge = node->edges;
        Edge *preedge = NULL;
        while(edge!=NULL){
            if (edge->node->name==name){
                if (preedge==NULL){
                    node->edges=edge->next;
                }else {
                    if (edge->next==NULL){
                        preedge->next = edge->next;
                    }else
                        preedge->next = edge->next;
                }
                free(edge);
                break;
            }
            preedge = edge;
            edge = edge->next;
        }
        elem = elem->next;
    }
}

void RenameNodes(Graph *a){
    Element *elem = a->nodes;
    int i=0;
    while (elem != NULL){
        Node *node = elem->node;
        node->name = i;
        i++;
        elem = elem->next;
    }
}

int DeleteNodeInGraph(Graph *a, int name){
    Element *elem = a->nodes;
    Element *preelem = NULL;
    while (elem!=NULL){
        if (elem->node->name==name){
            break;
        }
        preelem = elem;
        elem = elem->next;
    }
    if (elem==NULL){
        return 1;
    }
    Node *node = elem->node;
    Edge *edge = node->edges;
    Edge *preedge;
    while (edge!=NULL){
        preedge = edge;
        edge = edge->next;
        free(preedge);
    }
    DeleteEdges(a, name);
    free(node);
    if (preelem==NULL){
        if (elem->next==NULL){
            a->nodes = NULL;
        } else
            a->nodes = elem->next;
    } else {
        if (elem->next==NULL){
            preelem->next = NULL;
        } else
            preelem->next = elem->next;
    }
    RenameNodes(a);
    free(elem);
    a->kol--;
    return 0;
}

void TreeInit(Tree **a){
    *a = (Tree *) malloc(sizeof(Tree));
    (*a)->kol=0;
    (*a)->branch = (Tree **) calloc(1, sizeof(Tree));
}

void DeleteTree(Tree *a){
    if (a!=NULL) {
        for (int i = 0; i < a->kol; i++){
            DeleteTree(a->branch[i]);
        }
        free(a);
    }
}

void DFC_Visit(Node *node, int *color, Tree *root){
    if (node!=NULL && color[node->name]==WHITE){
        Edge *edge = node->edges;
        color[node->name]=BLACK;
        while (edge != NULL){
            if (color[edge->node->name]==WHITE){
                Tree *new;
                TreeInit(&new);
                new->name = edge->node->name;
                root->branch[root->kol]=new;
                root->kol++;
                DFC_Visit(edge->node, color, new);
            }
            edge = edge->next;
        }
    }
}

int SearchWayInTree(Tree *a, int name, int k){
    if (a!=NULL){
        k+=1;
        if (a->name==name){
            PrintElement(a, k);
            return 1;
        }
        for (int i=0; i<a->kol; i++){
            if (SearchWayInTree(a->branch[i], name, k)==1){
                PrintElement(a, k);
                return 1;
            }
        }
    }
    return 0;
}

void PrintTree(Tree *a, int kol){
    kol++;
    if (a!=NULL){
        for (int j=0; j<kol; j++){
            printf("    ");
        }
        printf("%d\n", a->name);
        for (int i=0; i<a->kol; i++){
            PrintTree(a->branch[i], kol);
        }
    }
}

int SearchInDeep(Graph *a, int name1, int name2){
    int k = a->kol;
    if (k==0){
        return -1;
    }
    Element *elemr = a->nodes;
    while (elemr->next!=NULL){
        elemr = elemr->next;
    }
    int *color = (int *) calloc((elemr->node->name+1), sizeof(int));
    Element *elem = a->nodes;
    while (elem!=NULL){
        if (elem->node->name==name1){
            break;
        }
        elem = elem->next;
    }
    if (elem==NULL){
        free(color);
        return 1;
    }
    Node *node = elem->node;
    Edge *edge = node->edges;
    if (edge==NULL){
        free(color);
        return 2;
    }
    color[node->name]=BLACK;
    Tree *root;
    TreeInit(&root);
    root->name = node->name;
    while (edge!=NULL){
        if (edge->node->name==name2 && color[edge->node->name]==WHITE){
            PrintNode(node);
            PrintNode(edge->node);
            DeleteTree(root);
            free(color);
            return 0;
        }
        if (color[edge->node->name]==WHITE) {
            Tree *new;
            TreeInit(&new);
            new->name = edge->node->name;
            root->branch[root->kol] = new;
            root->kol++;
            DFC_Visit(edge->node, color, new);
        }
        edge = edge->next;
    }
    if (root->kol==0){
        return 2;
    }
    //PrintTree(root, 0);
    int pos=0;
    if (SearchWayInTree(root, name2,pos)==0){
        return 2;
    }
    DeleteTree(root);
    free(color);
    return 0;
}

int *Search_Shortest(Graph *a, int name1, int name2){//алгоритм Бельмана-Форда
    if (a->kol==0){
        return NULL;
    }
    Element *elem2 = a->nodes;
    Node *node2;
    while (elem2!=NULL){
        node2 = elem2->node;
        if (node2->name==name1)
            break;
        elem2 = elem2->next;
    }
    if (elem2 == NULL){
        return NULL;
    }
    elem2 = a->nodes;
    while (elem2!=NULL){
        node2 = elem2->node;
        if (node2->name==name2)
            break;
        elem2 = elem2->next;
    }
    if (elem2 == NULL){
        return NULL;
    }

    if (name1 == name2){
        Element *elem = a->nodes;
        while (elem!=NULL){
            Node *node = elem->node;
            if (node->name==name1){
                break;
            }
            elem = elem->next;
        }
        if (elem==NULL){
            return NULL;
        }
        Edge *edge = elem->node->edges;
        while (edge!=NULL){
            if (edge->node->name==name1){
                int *p = (int *) malloc(sizeof(int)*3);
                p[0]=2; p[1]=name1; p[2]=name2;
                return p;
            }
            edge = edge->next;
        }
    }

    int *rast = (int *) malloc(sizeof(int)*a->kol);
    int *rastCur = rast;
    int *pred = (int *) malloc(sizeof(int)*a->kol);
    int *predCur = pred;

    for (int i=0; i<a->kol; i++){
        *(predCur++)=-1;//-1 - NULL
        *(rastCur++)= HIGH;
    }
    rast[name1]=0;
    for (int i=0; i<a->kol-1; i++){
        Element *elem = a->nodes;
        for (int j=0; j<a->kol; j++){
            Node *node = elem->node;
            Edge *edge = node->edges;
            while (edge!=NULL){
                if (rast[j]!=HIGH && rast[edge->node->name]>rast[j]+1){
                    rast[edge->node->name] = rast[j] + 1;
                    pred[edge->node->name] = j;
                }
                edge = edge->next;
            }
            elem = elem->next;
        }
    }

    int *p = NULL;
    if (pred[name2]!=-1){
        p = (int *) malloc(sizeof(int)*2);
        *p = 2;
        *(p+1)=name2;
        int prev = pred[name2];
        while(1){
            p=(int *) realloc(p, (*p+1)* sizeof(int));
            p[*p] = prev;
            if (prev==name1) break;
            *p +=1;
            prev = pred[prev];
        }
    }

    free(rast);
    free(pred);
    return p;
}

int SaveInFile(FILE *fp, Graph *a){
    fprintf(fp, "%d\n", a->kol);
    if (a->kol==0){
        return 1;
    }
    Element *elem = a->nodes;
    while (elem!=NULL){
        fprintf(fp, "%d %d\n", elem->node->x, elem->node->y);
        elem = elem->next;
    }
    elem = a->nodes;
    while(elem!=NULL){
        Node *node = elem->node;
        Edge *edge = node->edges;
        while (edge!=NULL){
            fprintf(fp, "%d ", edge->node->name);
            edge = edge->next;
        }
        fprintf(fp, "%d", -1);
        fprintf(fp, "\n");
        elem = elem->next;
    }
    fprintf(fp, "%d", -2);
    return 0;
}

int LoadFromFile(FILE *fp, Graph *a){
    int kol;
    fscanf(fp, "%d\n", &kol);
    if (kol==0){
        return 2;
    }
    printf("%d\n", kol);
    for (int i=0; i<kol; i++){
        int x, y;
        fscanf(fp, "%d %d\n", &x, &y);
        Node *add = (Node *) calloc(1, sizeof(Node));
        add->x = x;
        add->y = y;
        if (AddNodeInGraph(a, add)==1){
            return 1;
        }
    }
    int ver;
    int i=0;
    while (1){
        fscanf(fp, "%d", &ver);
        if (ver == -2)
            break;
        if (ver==-1){
            fscanf(fp, "\n");
            i++;
            continue;
        }
        int n = AddEdgeInGraph(a, i, ver);
        if (n==1 || n==2)
            return 3;
    }
}

void RandomGraph(Graph *a, int kol, int reb){
    for (int i=0; i<kol; i++){
        int x, y;
        x = rand();
        y = rand();
        Node *add = (Node *) calloc(1, sizeof(Node));
        add->x = x;
        add->y = y;
        if (AddNodeInGraph(a, add)==1){
            //printf("This coordinates are already have\n");
            continue;
        }
    }
    for (int i=0; i<reb; i++){
        int name1, name2;
        name1 = rand()%kol;
        name2 = rand()%kol;
        int n=AddEdgeInGraph(a, name1, name2);
        if (n==1){
            //printf("Node with 1-st name is absent!\n");
            continue;
        } else if (n==2){
            //printf("Node with 2-nd name is absent!\n");
            continue;
        }
    }
}

int NewSearchWayInTree(Tree *a, int name, int k){
    if (a!=NULL){
        k+=1;
        if (a->name==name){
            //PrintElement(a, k);
            return 1;
        }
        for (int i=0; i<a->kol; i++){
            if (NewSearchWayInTree(a->branch[i], name, k)==1){
                //PrintElement(a, k);
                return 1;
            }
        }
    }
    return 0;
}

int NewSearchInDeep(Graph *a, int name1, int name2){
    int k = a->kol;
    if (k==0){
        return -1;
    }
    Element *elemr = a->nodes;
    while (elemr->next!=NULL){
        elemr = elemr->next;
    }
    int *color = (int *) calloc((elemr->node->name+1), sizeof(int));
    Element *elem = a->nodes;
    while (elem!=NULL){
        if (elem->node->name==name1){
            break;
        }
        elem = elem->next;
    }
    if (elem==NULL){
        free(color);
        return 1;
    }
    Node *node = elem->node;
    Edge *edge = node->edges;
    if (edge==NULL){
        free(color);
        return 2;
    }
    color[node->name]=BLACK;
    Tree *root;
    TreeInit(&root);
    root->name = node->name;
    while (edge!=NULL){
        if (edge->node->name==name2 && color[edge->node->name]==WHITE){
            //PrintNode(node);
            //PrintNode(edge->node);
            DeleteTree(root);
            free(color);
            return 0;
        }
        if (color[edge->node->name]==WHITE) {
            Tree *new;
            TreeInit(&new);
            new->name = edge->node->name;
            root->branch[root->kol] = new;
            root->kol++;
            DFC_Visit(edge->node, color, new);
        }
        edge = edge->next;
    }
    if (root->kol==0){
        return 2;
    }
    //PrintTree(root, 0);
    int pos=0;
    if (NewSearchWayInTree(root, name2,pos)==0){
        return 2;
    }
    DeleteTree(root);
    free(color);
    return 0;
}

void Timing(double *add, double *sersh, double *serdfs, int n, int reb){
    Graph *a;
    clock_t start_ser, stop_ser;
    for (int j=0; j<5; j++) {
        InitGraph(&a);
        RandomGraph(a, n, reb);
        for (int i = 0; i < n; i++) {
            int start = rand() % n;
            int end = rand() % n;
            start_ser = clock();
            int k = NewSearchInDeep(a, start, end);
            if (k == 1 || k == -1 || k == 2) {
                //printf("Error!\n");
            }
            stop_ser = clock();
            *serdfs += (stop_ser - start_ser);
            start_ser = clock();
            int *p;
            if ((p=Search_Shortest(a, start, end)) == NULL) {
                //printf("Error!\n");
            }
            free(p);
            stop_ser = clock();
            *sersh += (stop_ser - start_ser);
        }
        GraphDelete(a);
    }
}
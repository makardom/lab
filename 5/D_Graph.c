#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "D_Graph.h"
#include <string.h>
#include <time.h>

void Menu(){
    printf("0. Exit\n1. Add node\n2. Add edge\n3. Delete node\n4. Delete edge\n5. Print graph\n6. Visualization\n7. Search way in deep\n8. Search shortest way\n9. Save In File\n10. Load from File\n11. Random Graph\n12. Timing\n");
    printf("Enter choice:");
}

void D_Start(Graph **a, int choice){
    if (*a==NULL){
        InitGraph(a);
    }
    switch (choice) {
        case 1:
            D_AddNodeInGraph(a);
            break;
        case 2:
            D_AddEdgeInGraph(a);
            break;
        case 3:
            D_DeleteNodeInGraph(a);
            break;
        case 4:
            D_DeleteEdgeInGraph(a);
            break;
        case 5:
            PrintGraph(*a);
            break;
        case 6:
            Visualisation(*a);
            break;
        case 7:
            D_SearchDFS(*a);
            break;
        case 8:
            D_Search_Shortest(*a);
            break;
        case 9:
            D_SaveInFile(*a);
            break;
        case 10:
            D_LoadFromFile(*a);
            break;
        case 11:
            D_Random_Graph(*a);
            break;
        case 12:
            D_Timing();
            break;
    }
}

void D_AddNodeInGraph(Graph **a){
    printf("Enter coordinate x:");
    int x;
    if (getInt(&x)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    printf("Enter coordinate y:");
    int y;
    if (getInt(&y)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    Node *add = (Node *) calloc(1, sizeof(Node));
    add->x = x;
    add->y = y;
    if (AddNodeInGraph(*a, add)==1){
        printf("This coordinates are already have\n");
        return;
    }
}

void D_AddEdgeInGraph(Graph **a){
    printf("Enter number of 1-st node (from):");
    int node1;
    if (getInt(&node1)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    printf("Enter number of 2-st node (in):");
    int node2;
    if (getInt(&node2)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    int n=AddEdgeInGraph(*a, node1, node2);
    if (n==1){
        printf("Node with 1-st name is absent!\n");
        return;
    } else if (n==2){
        printf("Node with 2-nd name is absent!\n");
        return;
    }else if (n==3){
        printf("This edge already has!\n");
        return;
    }
}

void D_DeleteNodeInGraph(Graph **a){
    printf("Enter name of node you want delete:");
    int name;
    if (getInt(&name)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    if (DeleteNodeInGraph(*a, name)==1){
        printf("Node with this name absent!\n");
        return;
    }
}

void D_DeleteEdgeInGraph(Graph **a){
    printf("Enter number of 1-st node (from):");
    int node1;
    if (getInt(&node1)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    printf("Enter number of 2-st node (in):");
    int node2;
    if (getInt(&node2)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    int n = DeleteEdgeInGraph(*a, node1, node2);
    if (n==1){
        printf("Node with 1-st name is absent!\n");
        return;
    } else if (n==2){
        printf("This edge is absent!\n");
        return;
    }
}

int CheckCoord(Graph *a, int name){
    Element *elem = a->nodes;
    int k=1;
    while(elem!=NULL && elem->node!=NULL){
        if (elem->node->name==name){
            break;
        }
        elem = elem->next;
        k++;
    }
    return k;
}

void PrintList(Graph *a){
    Element *elem = a->nodes;
    for (int i=0; i<a->kol; i++){
        Node *node = elem->node;
        printf("%d: ", node->name);
        Edge *edge = node->edges;
        while(edge!=NULL){
            printf("%d ", edge->node->name);
            edge = edge->next;
        }
        printf("\n");
        elem = elem->next;
    }
}

void PrintGraph(Graph *a){
    int k = a->kol;
    if (k==0){
        printf("Graph is empty!\n");
        return;
    }
    PrintList(a);
    return;
}

void D_SearchDFS(Graph *a){
    printf("Enter number of 1-st node (from):");
    int node1;
    if (getInt(&node1)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    printf("Enter number of 2-st node (in):");
    int node2;
    if (getInt(&node2)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    int n = SearchInDeep(a, node1, node2);
    if (n==-1){
        printf("Graph is empty!\n");
        return;
    } else if (n==1){
        printf("Node with 1-st name is absent!\n");
        return;
    } else if (n==2){
        printf("Way to node with 2-st name absent!!\n");
    }
}

void PrintWay(int *way){
    int *a = way + *way;
    for (int i=0; i<*way-1; i++){
        printf("%d->", *(a--));
    }
    printf("%d\n", *a);
}

void D_Search_Shortest(Graph *a){
    printf("Enter number of 1-st node (from):");
    int node1;
    if (getInt(&node1)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    printf("Enter number of 2-st node (in):");
    int node2;
    if (getInt(&node2)==-1){
        printf("Input Error!\n");
        return;
    }scanf("%*c");
    int *p;
    if ((p= Search_Shortest(a,node1, node2))==NULL){
        printf("Graph empty or some node is absent\n");
        printf("Or can't find way between nodes\n");
        return;
    }
    PrintWay(p);
    free(p);
}

void D_SaveInFile(Graph *a){
    printf("Enter file's name, where you want save graph:");
    char *name;
    if ((name=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    FILE *fp;
    if ((fp = fopen(name, "w+"))==NULL){
        printf("Cannot be opened!\n");
        free(name);
        return;
    }
    if(SaveInFile(fp, a)==1){
        printf("Graph is empty!\n");
    }
    fclose(fp);
    free(name);
}

void D_LoadFromFile(Graph *a){
    printf("Enter file's name, where you want take graph:");
    char *name;
    if ((name=get_str())==NULL){
        printf("Input Error!\n");
        return;
    }
    FILE *fp;
    if ((fp = fopen(name, "r"))==NULL){
        printf("Cannot be opened!\n");
        free(name);
        return;
    }
    int n=LoadFromFile(fp, a);
    if(n==2){
        printf("Graph is empty!\n");
    } else if (n==1){
        printf("This coordinates are already have\n");
    } else if (n==3){
        printf("Some of the nodes are missing\n");
    }
    fclose(fp);
    free(name);
}

void D_Random_Graph(Graph *a){
    srand(time(NULL));
    int kol = rand()+1;
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
    int koledge = rand();
    for (int i=0; i<koledge; i++){
        int name1, name2;
        name1 = rand()%kol;
        name2 = rand()%kol;
        int n=AddEdgeInGraph(a, name1, name2);
        if (n==1){
            printf("Node with 1-st name is absent!\n");
            continue;
        } else if (n==2){
            printf("Node with 2-nd name is absent!\n");
            continue;
        }else if (n==3){
            printf("This edge already has!\n");
            continue;
        }
    }
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
    return 0;
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

void Visualisation(Graph *a){
    FILE *fp;
    if ((fp = fopen("Graph.dot", "w+"))==NULL){
        printf("Cannot open file\n");
        return;
    }

    fprintf(fp, "digraph Graph {\n");


    Element *elem = a->nodes;
    while(elem != NULL){
        fprintf(fp, "\t%d [pos = \"%d,%d!\"]\n", elem->node->name, elem->node->x, elem->node->y);
        elem = elem->next;
    }
    elem = a->nodes;
    Node *node;
    Edge *edge;
    for (int i=0; i<a->kol; i++) {
        node = elem->node;
        edge = node->edges;
        while (edge != NULL) {
            fprintf(fp, "\t\"%d\" -> \"%d\"\n", node->name, edge->node->name);
            edge = edge->next;
        }
        elem = elem->next;
    }

    fprintf(fp, "}\n");
    fclose(fp);

    system("dot -Kfdp -n -Tpng -o Graph.png Graph.dot");
}

void PrintNode(Node *node){
    printf("%d\n", node->name);
    printf("|\n");
    printf("\\/\n");
}

void PrintElement(Tree *node, int k){
    printf("%d\n", node->name);
    if (k!=1) {
        printf("^\n");
        printf("|\n");
    }
}

void D_Timing(){
    FILE *fp;
    char *name = "TimeDFC.txt";
    if ((fp = fopen (name, "w+"))==NULL){
        free(name);
        printf("File cannot be opened\n");
        return;
    }
    FILE *fo;
    char *name1 = "TimeShort.txt";
    if ((fo = fopen (name1, "w+"))==NULL){
        free(name);
        printf("File cannot be opened\n");
        return;
    }

    clock_t start, end;
    double s_add, s_short, s_ser;
    fprintf(fp, "x;y\n");
    fprintf(fo, "x;y\n");
    start = clock();
    srand(time(NULL));
    for (int i=5; i<200; i+=5){
        s_add=0; s_short=0; s_ser=0;
        int kolreb = rand()%(i*i)+1;
        Timing(&s_add, &s_short, &s_ser, i, kolreb);
        s_ser = (double)((s_ser/CLOCKS_PER_SEC)/(i*5));
        s_short = (double)((s_short/CLOCKS_PER_SEC)/(i*5));
        fprintf(fp, "%d; %0.8lf\n", i+kolreb, s_ser);
        fprintf(fo, "%d; %0.8lf\n", i*kolreb, s_short);
    }
    end = clock();
    double all;
    all = (double) ((double) (end - start) / CLOCKS_PER_SEC);
    printf("Time to all: %0.6lf\n", all);
    fclose(fp);
    fclose(fo);
}

//int matr[k+1][k+1];
//for (int i=0; i<k+1; i++){
//for (int j=0; j<k+1; j++)
//matr[i][j]=0;
//}
//Element *elem = a->nodes;
//for (int j=1; j<k+1; j++){
//matr[0][j] = elem->node->name;
//elem = elem->next;
//}
//elem = a->nodes;
//for (int i=0; i<k; i++){
//printf("%d ", elem->node->name);
//elem = elem->next;
//}
//printf("\n");
//elem = a->nodes;
//for (int j=1; j<k+1; j++){
//matr[j][0] = elem->node->name;
//printf("%d ", matr[j][0]);
//elem = elem->next;
//}
//printf("\n");
//elem = a->nodes;
//Node *node;
//Edge *edges;
//int q=1;
//while (elem!=NULL){
//node = elem->node;
//edges = node->edges;
//while (edges!=NULL){
//int k = CheckCoord(a, edges->node->name);
//matr[q][k]+=1;
//edges = edges->next;
//}
//q++;
//elem = elem->next;
//}
//elem = a->nodes;
//for (int i=0; i<=k; i++){
//for (int j=0; j<=k; j++) {
//if (j==0 && i==0){
//printf("   ");
//continue;
//}
//printf("%d  ", matr[i][j]);
//}
//printf("\n");
//}
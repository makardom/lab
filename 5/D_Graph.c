#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "D_Graph.h"
#include <string.h>

void Menu(){
    printf("0. Exit\n1. Add node\n2. Add edge\n3. Delete node\n4. Delete edge\n5. Print graph\n6. Visualization\n");
    printf("Enter choice:");
}

int D_Start(Graph **a, int choice){
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
    }
}

void D_AddNodeInGraph(Graph **a){
    printf("Enter coordinate x:");
    int x;
    if (getInt(&x)==-1){
        printf("Input Error!\n");
        return;
    }
    printf("Enter coordinate y:");
    int y;
    if (getInt(&y)==-1){
        printf("Input Error!\n");
        return;
    }
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
    }
    printf("Enter number of 2-st node (in):");
    int node2;
    if (getInt(&node2)==-1){
        printf("Input Error!\n");
        return;
    }
    int n=AddEdgeInGraph(*a, node1, node2);
    if (n==1){
        printf("Node with 1-st name is absent!\n");
        return;
    } else if (n==2){
        printf("Node with 2-st name is absent!\n");
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
    }
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
    }
    printf("Enter number of 2-st node (in):");
    int node2;
    if (getInt(&node2)==-1){
        printf("Input Error!\n");
        return;
    }
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
    while(elem!=NULL){
        if (elem->node->name==name){
            break;
        }
        elem = elem->next;
        k++;
    }
    return k;
}

void PrintGraph(Graph *a){
    int k = a->kol;
    if (k==0){
        printf("Graph is empty!\n");
        return;
    }
    printf("k=%d\n", k+1);
    int matr[k+1][k+1];
    for (int i=0; i<k+1; i++){
        for (int j=0; j<k+1; j++)
            matr[i][j]=0;
    }
    Element *elem = a->nodes;
    for (int j=1; j<k+1; j++){
        matr[0][j] = elem->node->name;
        elem = elem->next;
    }
    elem = a->nodes;
    for (int j=1; j<k+1; j++){
        matr[j][0] = elem->node->name;
        elem = elem->next;
    }
    elem = a->nodes;
    Node *node;
    Edge *edges;
    int q=1;
    //printf("edge: %d\n", edges->name);
    while (elem!=NULL){
        node = elem->node;
        edges = node->edges;
        while (edges!=NULL){
            int k = CheckCoord(a, edges->node->name);
            matr[q][k]=1;
            edges = edges->next;
        }
        q++;
        elem = elem->next;
    }
    printf("ok\n");
    elem = a->nodes;
    for (int i=0; i<=k; i++){
        for (int j=0; j<=k; j++) {
            if (j==0 && i==0){
                printf("   ");
                continue;
            }
            printf("%d  ", matr[i][j]);
        }
        printf("\n");
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
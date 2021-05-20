#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void InitNode(Node *a){
    a = (Node *) calloc(1, sizeof(Node));
    a->edges = NULL;
}

void InitGraph(Graph **a){
    (*a) = (Graph *) malloc(sizeof (Graph));
    (*a)->nodes = (Element *) malloc(sizeof (Element));
    (*a)->nodes->node = NULL;
    (*a)->nodes->next = NULL;
    (*a)->kol = 0;
}

int AddNodeInGraph(Graph *a, Node *add){
    int i = 0;
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
    while (edge1!=NULL){
        if (node->name==name2)
            return 3;
        edge1 = edge1->next;
    }
    node = elem->node;
    edge1 = node->edges;
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
                    preedge->next = edge->next;
                }
                free(edge);
                return;
            }
            preedge = edge;
            edge = edge->next;
        }
        elem = elem->next;
    }
}

int DeleteNodeInGraph(Graph *a, int name){
    Element *elem = a->nodes;
    Element *preelem = NULL;
    while (elem->node!=NULL){
        if (elem->node->name==name){
            break;
        }
        preelem = elem;
        elem = elem->next;
    }
    if (elem->node==NULL){
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
    free(node);
    if (preelem==NULL){
        a->nodes = elem->next;
    } else {
        preelem->next = elem->next;
    }
    free(elem);
    DeleteEdges(a, name);
    a->kol--;
    return 0;
}


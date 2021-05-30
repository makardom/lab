#pragma once

#include "Graph.h"

void Menu();
void D_Start(Graph **a, int choice);
void D_AddNodeInGraph(Graph **a);
void D_AddEdgeInGraph(Graph **a);
int getInt(int *a);
char *get_str();
void PrintGraph(Graph *a);
void D_DeleteEdgeInGraph(Graph **a);
void D_DeleteNodeInGraph(Graph **a);
void Visualisation(Graph *a);
void PrintNode(Node *node);
void D_SearchDFS(Graph *a);
void PrintElement(Tree *node, int k);
void D_Search_Shortest(Graph *a);
void D_SaveInFile(Graph *a);
void D_LoadFromFile(Graph *a);
void D_Random_Graph(Graph *a);
void D_Timing();
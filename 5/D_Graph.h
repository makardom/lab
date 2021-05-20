#pragma once

#include "Graph.h"

void Menu();
int D_Start(Graph **a, int choice);
void D_AddNodeInGraph(Graph **a);
void D_AddEdgeInGraph(Graph **a);
int getInt(int *a);
void PrintGraph(Graph *a);
void D_DeleteEdgeInGraph(Graph **a);
void D_DeleteNodeInGraph(Graph **a);
void Visualisation(Graph *a);
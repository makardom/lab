#include <stdio.h>
#include "Graph.h"
#include "D_Graph.h"


int main() {
    Graph *a;
    a = NULL;
    int flag = 1;
    while (flag){
        Menu();
        int choice;
        if (getInt(&choice)==-1){
            printf("Input Error!\n");
        }
        scanf("%*c");
        if (choice==0){
            flag = 0;
        }else if (choice>0 && choice<=12){
            D_Start(&a, choice);
        } else
            printf("Enter correct number!\n");
    }
    return 0;
}

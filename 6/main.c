#include <stdio.h>
#include <stdlib.h>
#include "BinaryHeap.h"
#include "Functions.h"


int main() {
    Node **nodes=NULL;
    int flag =1;
    while(flag){
        Menu();
        int choice;
        if (getInt(&choice)==-1){
            printf("Input Error!\n");
            continue;
        }
        scanf("%*c");
        if (choice==0){
            printf("Goodbye!\n");
            //DeleteArray(array);
            flag=0;
        }else if (choice>0 && choice<11){
            D_Start(&nodes, choice);
        }
    }
    return 0;
}

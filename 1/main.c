#include <stdio.h>
#include "library.h"



int main(){
    Matrix matr={0,NULL};//initial matrix
    Matrix new={0,NULL};
    Matrix second = {0, NULL};
    if( input( &matr ) ==0){
        printf("End of file occured\n");
        return 1;
    }

    printf("Old matrix:");
    output(&matr);

    NewMatrix(&new, &matr, &second);

    printf("New matrix:");
    output(&new);

    printf("Second matrix:");
    output(&second);

    clear(&matr);
    clear(&new);
    clear(&second);
    printf("End\n");
}

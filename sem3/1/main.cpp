#include <iostream>
#include "Prog1.h"

using namespace SparsMatrix;

int main()
{
    Line *lines = nullptr;
    int m;
    int n;
    lines = random_input(m,n);
    if (!lines){
        std::cout<<"incorrect data"<<std::endl;
        return 1;
    }
    Line *tran = nullptr;
    int k;
    k=transformation(lines, tran, m, n);
    if (k==1){
        std::cout<<"incorrect data"<<std::endl;
        return 1;
    }
    output("Initial Matrix", lines, m,n);
    output("Transformed matrix", tran, m, n);

    erase(lines, m);
    erase(tran, m);

    return 0;
}

#include "Sequence.h"

namespace Prog3{
    Sequence::Sequence(int num) {
        amount = 1;
        mass[0] = num;
    }

    Sequence::Sequence(int k, const int a[]) {
        if (k>SZ){
            throw std::runtime_error("Entered amount more than possible");
        }
        amount = k;
        for (int i=0; i<k; i++){
            mass[i]=a[i];
        }
    }
    inline const int *Sequence::getMass() const {
        return mass;
    }
}
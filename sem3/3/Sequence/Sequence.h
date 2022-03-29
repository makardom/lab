#ifndef LAB3_SEQUENCE_H
#define LAB3_SEQUENCE_H

#include <iostream>

namespace Prog3{
    class Sequence{
    private:
        static const int SZ = 100;
        int amount;
        int mass[SZ]{};
    public:
        Sequence() :amount(0){}
        explicit Sequence(int num);
        Sequence(int k, const int a[]);
        inline int getAmount() const{return amount;}
        inline const int *getMass() const;
        std::ostream & print(std::ostream&) const;
        Sequence & join(Sequence &a, Sequence &b);
        int *order()const;
        Sequence & AddNewElem(int elem);
        int groups()const;
        int frequency(int num)const;
    };
}
#endif //LAB3_SEQUENCE_H

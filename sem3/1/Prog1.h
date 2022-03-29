#ifndef INC_1_PROG1_H
#define INC_1_PROG1_H
#include <iostream>
namespace SparsMatrix {

    struct Element{
        int pos;
        double num;
    };

    struct Line {
        int n;
        Element *a;
    };

    template<class T>
    int getNum(T &a){
        while(true) {
            std::cin >> a;
            if (std::cin.good()==1) {
                return 1;
            }
            if (std::cin.eof()==1){
                return -1;
            }
            std::cout<<"repeat enter!";
            std::cin.clear();
            std::cin.ignore();
        }
    }

    Line *input(int &m, int &n);
    Line *random_input(int &rm, int &rn);
    void output(const char *msg, Line a[], int m, int n);
    Line *erase(Line *&a, int m);
    int transformation(Line *&lines, Line *&trans, int m, int n);
    void shaker_increase(Element *line, int n);
    void shaker_decrease(Element *line, int n);
    void output_sec(const char *msg, Line a[], int m);
    int CheckPosition(Element *elem, int pos, int n, int k);
    void Transform_Position_Inc(Element *elem, int n, int k);
    void Transform_Position_Dec(Element *elem, int n, int k);
}

#endif //INC_1_PROG1_H

#include <iostream>
#include <ctime>
#include "Prog1.h"

//#define a(x) std::cout<<x<<std::endl;

namespace SparsMatrix{

    Line* input(int &rm, int &rn)
    {
        const char *pr = "";
        Line *lines = nullptr;
        int m;
        do{
            std::cout << pr << std::endl;
            std::cout << "Enter number of lines: -->";
            pr = "You are wrong; repeat please!";
            if (getNum(m) < 0)
                return nullptr;
        } while (m < 1);
        try{
            lines = new Line[m];
        }
        catch (std::bad_alloc &ba)
        {
            std::cout << "------Error------" << ba.what() << std::endl;
            return nullptr;
        }
        int n;
        pr = "";
        do{
            std::cout << pr << std::endl;
            std::cout << "Enter number of items in lines -->";
            pr = "You are wrong; repeat please!";
            if (getNum(n) < 0){
                erase(lines, 0);
                return nullptr;
            }
        } while (n < 1);

        for (int i = 0; i < m; i++){
            std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
            pr = "";
            do{
                std::cout<<pr<<std::endl;
                std::cout<<"Enter amount of non-zero numbers -->";
                pr = "You are wrong; repeat please!";
                if (getNum(lines[i].n)<0){
                    erase(lines, 0);
                    return nullptr;
                }
            }while(lines[i].n<0);
            try{
                lines[i].a = new Element [lines[i].n];
            }catch (std::bad_alloc &ba){
                std::cout<<"------Error------"<<std::endl;
                return nullptr;
            }

            for (int j = 0; j < lines[i].n; j++) {
                int check;
                do{
                    check = 0;
                    std::cout << "Enter position " << (j + 1) << " number -->";
                    if (getNum(lines[i].a[j].pos) < 0) {
                        erase(lines, i + 1);
                        return nullptr;
                    }
                    int ch = CheckPosition(lines[i].a, lines[i].a[j].pos, n, j);
                    if (ch == 1) {
                        std::cout<<"Entered position not exist"<<std::endl;
                        check = -1;
                    }
                    else if (ch == 2){
                        std::cout<<"This position already busy, repeat"<<std::endl;
                        check=-1;
                    }
                }while(check<0);
                std::cout<<"Enter number:";
                if (getNum(lines[i].a[j].num)<0){
                    erase(lines, i+1);
                    return nullptr;
                }
            }

        }
        rn = n;
        rm = m;
        return lines;
    }

    Line *random_input(int &rm, int &rn){
        Line *lines = nullptr;
        int m;
        srand(time(0));
        m = rand()%200;
        try{
            lines = new Line[m];
        }
        catch (std::bad_alloc &ba)
        {
            std::cout << "------Error------" << ba.what() << std::endl;
            return nullptr;
        }
        int n;
        n = rand()%100;
        for (int i = 0; i < m; i++){
            lines[i].n = rand() % n;
            try{
                lines[i].a = new Element [lines[i].n];
            }catch (std::bad_alloc &ba){
                std::cout<<"------Error------"<<std::endl;
                return nullptr;
            }

            for (int j = 0; j < lines[i].n; j++) {
                int check;
                do{
                    check = 0;
                    lines[i].a[j].pos = rand()%n;
                    int ch = CheckPosition(lines[i].a, lines[i].a[j].pos, n, j);
                    if (ch == 1) {
                        check = -1;
                    }
                    else if (ch == 2){
                        check=-1;
                    }
                }while(check<0);
                lines[i].a[j].num = rand();
            }
        }
        rn = n;
        rm = m;
        return lines;
    }

    void Sort_Element(Element *&a, int n){
        int left = 0, right=n-1;
        int flag=1;
        while((left<right)&&flag>0){
            flag=0;
            for (int i=left; i<right; i++){
                if (a[i].pos>a[i+1].pos){
                    Element per = a[i];
                    a[i] = a[i+1];
                    a[i+1] = per;
                    flag=1;
                }
            }
            right--;
            for (int i=right;i>left; i--){
                if (a[i].pos<a[i-1].pos){
                    Element per = a[i];
                    a[i] = a[i-1];
                    a[i-1] = per;
                    flag=1;
                }
            }
            left++;
        }
    }

    void output(const char *msg, Line *lines, int m, int n)
    {
        int i, j;
        std::cout << msg << ":\n";
        for (i=0; i<m; i++){
            Sort_Element(lines[i].a, lines[i].n);
            int k=0;
            if (lines[i].n==0){
                for (j=0; j<n; j++)
                    std::cout<<"0   ";
            }else {
                for (j = 0; j < n; j++) {
                    if (j == lines[i].a[k].pos) {
                        std::cout << lines[i].a[k].num << "   ";
                        k++;
                    } else {
                        std::cout << "0   ";
                    }
                }
            }
            std::cout<<std::endl;
        }
    }

    void output_sec(const char *msg, Line *lines, int m){
        int i, j;
        std::cout << msg << ":\n";
        for (i=0; i<m; i++) {
            for(j=0; j<lines[i].n; j++){
                std::cout<<lines[i].a[j].num<<"   ";
            }
            std::cout<<std::endl;
        }
    }

    Line *erase(Line *&lines, int m)
    {
        int i;
        for (i = 0; i < m; i++)
            delete[] lines[i].a;
        delete[] lines;
        return nullptr;
    }

    int CopyMatrix(Line *first, Line *&second, int m){
        for(int i=0; i<m; i++){
            second[i].n=first[i].n;
            try{
                second[i].a = new Element[first[i].n];
            }
            catch (std::bad_alloc &ba)
            {
                std::cout << "------Error------" << ba.what() << std::endl;
                return 1;
            }
            for (int j=0; j<first[i].n; j++){
                second[i].a[j].num = first[i].a[j].num;
                second[i].a[j].pos = first[i].a[j].pos;
            }
        }
        return 0;
    }

    int transformation(Line *&lines, Line *&tran, int m, int n)
    {
        try{
            tran = new Line[m];
        }
        catch (std::bad_alloc &ba)
        {
            std::cout << "------Error------" << ba.what() << std::endl;
            return 1;
        }
        if (CopyMatrix(lines, tran, m)>0){
            return 1;
        }
        int i,j;
        for (i=0; i<m; i++){
            int flag = 0;
            for (j=0; j<tran[i].n; j++){
                if (tran[i].a[j].pos==0)
                    flag=j;
            }
            if (tran[i].a[flag].num<=0 || flag==0){
                shaker_increase(tran[i].a, tran[i].n);
                Transform_Position_Inc(tran[i].a, n, tran[i].n);
            }else{
                shaker_decrease(tran[i].a, tran[i].n);
                Transform_Position_Dec(tran[i].a, n, tran[i].n);
            }
        }

        return 0;
    }

    void shaker_increase(Element *line, int n){
        int left=0, right= n - 1;
        int flag=1;
        while((left<right)&&flag>0){
            flag=0; //показывает, что перемещений не было
            for (int i=left; i<right;i++){
                if (line[i].num > line[i + 1].num){
                    std::swap(line[i], line[i+1]);
                    flag=1; //указатель на то, что было выполнено перемещение
                }
            }
            right--; // смещение правой границы на предыдущий элемент
            for (int i=right; i>left; i--){
                if (line[i].num < line[i - 1].num){
                    std::swap(line[i], line[i-1]);
                    flag=1;
                }
            }
            left++; //смещение границы слева на следующий элемент
        }
    }

    void shaker_decrease(Element *line, int n){
        int left=0, right= n - 1;
        int flag=1;
        while((left<right)&&flag>0){
            flag=0;
            for (int i=left; i<right;i++){
                if (line[i].num < line[i + 1].num){
                    std::swap(line[i], line[i+1]);
                    flag=1;
                }
            }
            right--;
            for (int i=right; i>left; i--){
                if (line[i].num > line[i - 1].num){
                    std::swap(line[i], line[i-1]);
                    flag=1;
                }
            }
            left++;
        }
    }

    void Transform_Position_Inc(Element *elem, int n, int k){
        for (int i=0; i<k; i++){
            if (elem[i].num<0){
                elem[i].pos=i;
            }else{
                elem[i].pos = i+(n-k);
            }
        }
    }

    void Transform_Position_Dec(Element *elem, int n, int k){
        for (int i=0; i<k; i++){
            if (elem[i].num>0){
                elem[i].pos = i;
            }else{
                elem[i].pos = i+(n-k);
            }
        }
    }

    int CheckPosition(Element *elem, int pos, int n, int k){
        if (pos>n-1)
            return 1;
        for (int i=0; i<k; i++){
            if (pos==elem[i].pos)
                return 2;
        }
        return 0;
    }
}
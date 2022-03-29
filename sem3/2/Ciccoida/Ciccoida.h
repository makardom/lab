#ifndef INC_2_CICCOIDA_H
#define INC_2_CICCOIDA_H
#include <cmath>
#include <iostream>

namespace Prog2 {
    template<class T>
    int getNum(T &a){/*функция принимает ссылку на число любого типа(целое, действительное)
                       и присваивает ему считанное с клавиатуры число*/
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
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    }

    class Ciccoida {
    private:
        double a; //радиус окружности
    public:
        Ciccoida(double rad = 1);//пустой конструктор, а также инициализирующий конструктор
        Ciccoida(const Ciccoida &ciccoida);//копирующий конструктор
        //сеттеры - set'теры
        Ciccoida& set(double a0){a=a0; return *this;}
        //геттеры - get'теры
        double get() const{return a;}
        //другие методы
        double square() const{ return 3*M_PI*a*a; }//вычисление площади полосы между циссоидой и ее асимптотой
        double distance(double grad = 0) const;//расстояние до центра в полярной системе
        double value_y(double x=1) const;//значение y в декартовой системе координат по указанному x
        double asymptote() const { return 2*a; }//коэффициент в уравнении асимптоты
        double volume () const;//объем тела, полученной вращением полосы вокруг асимптоты
        double coefficient() const;//коэффициенты в уравнении параболы такой, что основания перпендикуляров, опущенных из вершины параболы на ее касательные, образуют данную циссоиду.
    };

}
#endif //INC_2_CICCOIDA_H

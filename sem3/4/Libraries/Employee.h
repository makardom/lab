#ifndef LAB4_EMPLOYEE_H
#define LAB4_EMPLOYEE_H

#include "Worker.h"

/*!
 * \brief Дочерний класс "Рабочий"
 * \details Дочерний класс "Рабочий", который наследует класс "Работник"
 */

class Employee: public Worker{
private:
    int QualityAdd;///Значение, характеризующее его аддитивный вклад в увеличение дневной выработки группы на объекте(целое значение [1..10])
public:
    /*!
     * Пустой конструктор
     */
    Employee():Worker(),QualityAdd(0){}
    /*!
     * Конструктор с указанными значениями
     * @param Num Уникальный номер рабочего
     * @param name Имя рабочего
     * @param age Возраст рабочего
     * @param quality Аддитивный вклад рабочего
     */
    Employee(const int Num, const std::string& name, const int age, const int quality):Worker(Num, name, age), QualityAdd(quality){}
    ~Employee() = default;
    /*!
     * Метод, который изменяет значение int в паре чисел, путем добавления (+) вклада работника
     * @param a Пара чисел <int, double>
     * @return Пару чисел с измененным значением int
     */
    void getQuality(std::pair<int, double> &a) const override;
    /*!
     * Изменяет значение Аддитивного вклада рабочего
     * @param change Значение, на которое меняется аддитивный вклад
     */
    int ChangeQuality(int change);
    /*!
     * Выводит имя класса "Рабочий" и значение аддитивного вклада
     * @param s std::cout
     */
    void PrintClass(std::ostream &s) const override;
};


#endif //LAB4_EMPLOYEE_H

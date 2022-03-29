#ifndef LAB4_MASTER_H
#define LAB4_MASTER_H
#include "Worker.h"
#include "Employee.h"

/*!
 * \brief Класс "Мастер"
 * \details Класс "Мастер", который наследует класс "Работник"
 */

class Master:public Worker{
private:
    double QualityMulti;///Мультипликативный вклад в увеличение дневной выработки на учатске (double [1..5])
public:
    /*!
     * Пустой конструктор
     */
    Master(): Worker(), QualityMulti(0){}
    /*!
     * Конструктор, который из класса "Рабочий" делает класс "Мастер"
     * @param a экзеспляр класса "Рабочий"
     */
    explicit Master(Employee *a);
    /*!
     * Конструктор
     * @param Num Уникальный номер мастера
     * @param name Имя мастера
     * @param age Возраст мастера
     * @param quality Мультипликативный вклад мастера
     */
    Master(const int Num, const std::string& name, const int age, const double quality):Worker(Num, name, age), QualityMulti(quality){}

    ~Master() = default;
    /*!
     * Метод, который изменяет значение double в паре чисел, путем умнажения на вклад мастера
     * @param a Пара чисел <int, double>
     * @return Пару чисел с измененным значением double
     */
    void getQuality(std::pair<int, double> &a) const override;
    /*!
     * Изменение значения мультипликативного вклада мастера
     * @param change Новое занчение вклада мастера
     */
    int ChangeQuality(double change);
    /*!
     * Выводит имя класса "Мастер" и значение мультипликативного вклада
     * @param s std::cout
     */
    void PrintClass(std::ostream &s) const override;

    void CopyFrEn(std::map<int, Worker *> fr, std::map<int, Worker *> en);
};


#endif //LAB4_MASTER_H

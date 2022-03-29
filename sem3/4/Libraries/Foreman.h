#ifndef LAB4_FOREMAN_H
#define LAB4_FOREMAN_H
#include "Worker.h"

/*!
 * \brief Класс "Бригадир"
 * \details Класс "Бригадир", который наследует класс "Работник"
 */

class Foreman:public Worker{
private:
    int PlotNumber;///Число участка работ, к которому он прикреплен на данный момент, -1 - если ни к какому участку
public:
    /*!
     * Конструктор
     * @param region Уникальный номер участка работ(если не указан, то равен -1)
     */
    explicit Foreman(int region=-1):Worker(), PlotNumber(region){}

    ~Foreman() = default;
    /*!
     * Геттер
     * @return Уникальный номер участка работ, на котором находится бригадир
     */
    int getPlotNumber() const{return PlotNumber;}

    void getQuality(std::pair<int, double> &) const override{}
    /*!
     * Изменяет Уникальный номер участка работ, на котором находится бригадир
     * @param num Уникальный номер участка работ, на который был отправлен бригадир
     * @return
     */
    void ChangePlot(int num);
    /*!
     * Выводит имя класса "Бригадир" и Номер участка, на котором он сейчас находится
     * @param s std::cout
     */
    void PrintClass(std::ostream &s) const override;
};


#endif //LAB4_FOREMAN_H

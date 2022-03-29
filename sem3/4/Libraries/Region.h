#ifndef LAB4_REGION_H
#define LAB4_REGION_H
#include "Master.h"
#include "Employee.h"
#include "Foreman.h"
#include <map>

/*!
 * \brief Класс "Участок работ"
 */

class Region {
private:
    int Number;///Уникальный номер учатска работ
    double Volume;///Объем работ на участке
    int Days;///Количество дней до завершения работ на участке(вычисляется автоматически)
    Worker *RForeman;///Бригадир, который прикреплен к участку(если его нет на участке, то указывает на nullptr)
    std::map<int, Worker *> Workers;///Массив работников на данном участке
    /*!
     * Вычисляет какое количество дней осталось для завершения работы на участке
     */
    int CalculateDays();
    /*!
     * Допольнительный метод, который выесняет сколько общих друзей имеют двое работников на участке
     * @param a Друзья первого работника
     * @param b Друзья второго работника
     */
    int CountMutualFriend(const std::map<int, Worker *> &a,const std::map<int, Worker *> &b);
public:
//    friend class Iterator;
//
//    Iterator begin(){return Workers;}
//    Iterator end(){return Workers+_n;}
    /*!
     * Пустой контсруктор
     */
    Region():Number(0),Volume(0),Days(-1),RForeman(nullptr),Workers(){}
    /*!
     * Конструктор учатска работ с указанным уникальным номером
     * @param num Уникальный номер
     */
    explicit Region(const int num):Number(num), Volume(0), Days(-1), RForeman(nullptr), Workers(){}
    /*!
     * Конструктор учатска работ с указанным уникальным номером и объемом
     * @param num Уникальный номер
     * @param vol Объем работ
     */
    Region(const int num, double vol): Number(num), Volume(vol), Days(-1), RForeman(nullptr), Workers(){}
    /*!
     * Конструктор учатска работ с указанным уникальным номером, объемом и массивом работником
     * @param num
     * @param vol
     * @param workers
     */
    Region(int num, double vol, std::map<int,Worker*> workers);

    ~Region() = default;
    /*!
     * Геттер
     * @return Уникальный номер учатска
     */
    int getNumber() const {return Number;}
    /*!
     * Геттер
     * @return Объем работ на участке
     */
    double getVolume() const {return Volume;}
    /*!
     * Геттер
     * @return Количество дней до окончания работ на участке
     */
    int getDays() const{return Days;}
    /*!
     * Проверка на наличие работника на данном учатске
     * @param num Уникальный номер работника
     */
    int CheckWorkerByKey(int num);
    /*!
     * Изменяет значение объема работ на участке
     * @param vol Новое значение объема работ
     */
    void ChangeVolume(double vol);
    /*!
     * Добавляет работника на участко работ
     * @param a Новый работник на участке
     */
    void AddWorker(Worker *a);
    /*!
     * Прикрепляет бригадира к данному участку
     */
    void AppointForeman(Worker *);
    /*!
     * Убирает работника с этого участка работ
     * @param num Уникальный номер работника
     */
    void RemoveWorker(int num);
    /*!
     * Открепляет бригадира от данного участка
     */
    void RemoveForeman();
    /*!
     * Вывод данных об участке
     * @param s std::cout
     * @param a Участок работ
     */
    friend std::ostream & operator <<(std::ostream &s, Region *a);
    /*!
     * Вычисление выработки на участке за один день
     * @return Значение выработки на учатске
     */
    double WorkingOut();//выработка на участке
    /*!
     * Создает новые отношения(дружественные и враждебные одновременно) на участке работ
     */
    void MakeRelationships();
    /*!
     * Моделирование рабочего дня
     */
    void WorkDay();

    void MakeRemarks();

    Worker * getForeman() const{ return RForeman;}

    const std::map<int, Worker*>& getWorkers() const{ return Workers;}
};


#endif //LAB4_REGION_H

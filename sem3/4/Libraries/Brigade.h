#ifndef LAB4_BRIGADE_H
#define LAB4_BRIGADE_H
#include "Region.h"
#include "MyMap.h"
#include <map>
#include <fstream>

/*!
 * \brief Класс "Бригада"
 */

class Brigade {
private:
    Worker *BForeman;///Бригадир, без которого бригада не может существовать
    //std::map<int, Worker*>
    Map::MyMap<int, Worker *> Workers;///Массив Работников, которые работают в бригаде
    std::map<int, Region*> Regions;///Массив Участков работ
    /*!
     * Проверка на наличие работника с указанным уникальным номером
     * @param num Уникальный номер работника
     * @return -1 в случае, если работник не найден, 0 - если найден
     */
    int CheckWorkerByKey(int num);
    /*!
     * Проверка на наличие участка с указанным уникальным номером
     * @param num Уникальный номер участка
     * @return -1 в случае, если участок не найден, 0 - если найден
     */
    int CheckRegionByKey(int num);
//    void ExtraComputation(double &total);
public:
    /*!
     * Пустой конструктор
     */
    Brigade(): BForeman(nullptr), Workers(), Regions(){}

    ~Brigade() = default;
//    Brigade(Brigade&) = default;
//    Brigade(Brigade&&);
//    const std::map<int, Worker *>& getWorkers() const{ return Workers;}
    const Map::MyMap<int, Worker *>& getWorkers() const{ return Workers;}
    const std::map<int, Region *>& getRegions() const{ return Regions;}
    Worker * getForeman() const{ return BForeman;}
    /*!
     * Изменяет значение объема работ на участке, номер которого указан
     * @param vol Новый объем работ
     * @param num Уникальный номер участка
     * @return -1 в случае, если региона с таким номером не существует
     */
    int ChangeInRegion(double vol, int num);
    /*!
     * Добавляет работника к участку работ
     * @param numw Уникальный номер работника
     * @param numr Уникальный номер участка работ
     */
    void AppointWorkerInRegion(int numw, int numr);
    /*!
     * Метод, который назначает прикрепляет пригадира к бригаде работников
     * @param a Бригадир
     */
    void AddForeman(Worker *a);
    /*!
     * Метод, который добавляет нового работника в бригаду
     * @param a Новый работник
     */
    void AddWorker(Worker *a);
//    Brigade& AddNewMaster(Master &);
//    Brigade& AddNewEmployee(Employee &);
    /*!
     * Увольнение работника из бригады
     * @param num Уникальный номер работника
     */
    void FireWorker(int num);
    /*!
     * Добавление нового участка работ для бригады
     * @param add Новый участок работ
     */
    void AddNewRegion(Region *add);
    /*!
     * Удаление участка работ бригады
     * @param num Уникальный номер учатска работ
     */
    void DeleteRegion(int num);
    /*!
     * Получение данных о выработке на указанном участке
     * @param num Уникальный номер участка
     * @return Значение выработки на участке
     */
    double PerformanceData(int num) const;
    /*!
     * Получение данных о выполнении всех поставленных задач
     * @return 1 - если по окончанию этого дня все задачи будут выполнены, 0 - если нет
     */
    int CompleteWork() const;
    /*!
     * Получение данных о наиболее проблемном участке на данный момент
     * @return Уникальный номер проблемного участка
     */
    int MostProblem() const;
    /*!
     * Повышение рабочего до мастера с указанием нового значения качества работы
     * @param num Уникальный номер работника
     * @param qual Новое значение качества работы
     */
    void UpgradeToMaster(int num, double qual);


    int MakeANewFriends(int num1, int num2);


    int MakeANewEnemy(int num1, int num2);

    int AppointForeman(int num);
    /*!
     * Вывод данных о бригаде
     * @param s std::cout
     * @param br Бригада
     * @return Значения экземпляра класса "Бригада"
     */
    friend std::ostream &operator <<(std::ostream &s, Brigade &br);
    /*!
     * Моделирование рабочего дня
     */
    void PassDay();

    void DeleteFromRegion(int numw, int numr);

    void ClearAll();

    void RecordFile(std::ofstream &f);

    void ReadFromFile(std::ifstream &f);
};


#endif //LAB4_BRIGADE_H
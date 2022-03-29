#ifndef LAB4_WORKER_H
#define LAB4_WORKER_H
#include <iostream>
#include <map>
#include <utility>

/*!
 * \brief Базовый класс "Работник"
 * \details Базовый класс "Работник", который наследуется классами "Рабочий", "Мастер", "Бригадир"
 */

class Worker {
protected:
    int Number;///Уникальный номер работника
    std::string Name;///Имя работника
    int Age;///Возраст работника
    std::map<int, Worker *>Friends;///Массив работников, которые являются друзьями
    std::map<int, Worker *>Enemies;///Массив работников, которые являются врагами
public:
    /*!
     * Пустой конструктор класса "Работник", который для "Номер", "Возраст" равны 0, нет "Друзей" и "Врагов"
     */
    Worker():Number(0),Age(0),Friends(), Enemies(){}
    /*!
     * Конструктор, который по переданным данным создает экземпляр класса "Работник" с указанными значениями
     * @param[in] Num Уникальный номер работника
     * @param[in] name Имя работника
     * @param[in] age Возраст работника
     */
    Worker(int Num, std::string name, int age):Number(Num), Name(std::move(name)), Age(age), Friends(), Enemies(){}

    virtual ~Worker() = default;
////    Worker(Worker &);
////    Worker(Worker &&);
    //Getters
    /*!
     * Геттер
     * @return Уникальный номер работника
     */
    int getNumber() const{return Number;}
    /*!
     * Геттер
     * @return Имя работника
     */
    std::string getName() const {return Name;}
    /*!
     * Геттер
     * @return Возраст работника
     */
    int getAge() const {return Age;}
    /*!
     * Геттер
     * @return Массив работников, которые являются друзьями
     */
    const std::map<int, Worker*>& getFriends() const {return Friends;}
    /*!
     * Геттер
     * @return Массив раюотников, которые являются врагами
     */
    const std::map<int, Worker*>& getEnemies() const {return Enemies;}
    /*!
     * Сеттер, который изменяет "Номер", "Имя", "Возраст". Объединен, т.к. используется, когда создается новый экземпляр дочернего класса
     * @param num Уникальный номер работника
     * @param name Имя работника
     * @param age Возраст работника
     */
    void set(int num, const std::string& name, int age);

    virtual void getQuality(std::pair<int, double> &) const = 0;

    virtual void PrintClass(std::ostream &s) const = 0;
    /*!
     * Вывод данных
     * @param s std::cout
     * @param a указатель на класс "Работник"
     * @return Значения экземпляра класса "Работник"
     */
    friend std::ostream & operator <<(std::ostream &s, Worker *a);
    /*!
     * Добавляет нового друга в массив друзей
     * @param fr Указатель класса "Работник", который указывает на нового друга
     */
    void AddNewFriend(Worker *fr);
    /*!
     * Добавляет нового врага в массив врагов
     * @param en Указатель класса "Работник", который указывает на нового врага
     */
    void AddNewEnemy(Worker *en);
    /*!
     * Удаляет друга из массива друзей
     * @param num Уникальный номер друга, которого нужно убрать
     */
    void DeleteFriend(int num);
    /*!
     * Удаляет врага из массива врагов
     * @param num Уникальный номер врага, которого нужно убрать
     */
    void DeleteEnemy(int num);

    bool operator != (const Worker *b);
//    void MakeFriend(std::map<int, Worker *>list);
//    void MakeEnemy(std::map<int, Worker *>list);
};


#endif //LAB4_WORKER_H



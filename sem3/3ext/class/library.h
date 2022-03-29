#ifndef LAB2_LIB_LIBRARY_H
#define LAB2_LIB_LIBRARY_H
#include <iostream>
#include <cstring>
#include <string>

//const int size_of_string=45;

template<typename T>

int getNum(T &a);

std::string get_str();

class element_of_table{
private:
    int key;
    std::string name;
public:
    element_of_table() noexcept;//Инициализирующий конструктор(по умолчанию) 1 для элемента таблицы

    element_of_table(int k, std::string n) noexcept;//Инициализирующий конструктор 2 для элемента таблицы

    element_of_table(const element_of_table& other) noexcept;//Копирующий конструктор для элемента таблицы

    element_of_table(element_of_table&& other) noexcept;//Конструктор перемещения для элемента таблицы

    ~element_of_table() noexcept = default;//Деструктор для элемента таблицы

    element_of_table& operator = (const element_of_table& other) noexcept;//Перегрузка оператора присваивания копированием для элемента

    element_of_table& operator = (element_of_table&& other) noexcept;//Оператор присваивания перемещением для элемента

    friend std::istream& operator >> (std::istream &c, element_of_table& elem);//Перегруженный оператор потока ввода

    int get_key() const noexcept{ return key; }//Геттер, возвращающий ключ, хранящийся в элементе таблицы

    std::string get_name() const noexcept { return name; }//Геттер, возвращающий текстовую строку, хранящуюся в элементе таблицы

    std::string set_name(std::string n) noexcept;//Сеттер, меняющий значение текстовой строки, хранящейся в элементе таблицы

    int set_key(int k) noexcept;//Сеттер, меняющий значение ключа, хранящегося в элементе таблицы

};

class Table {
private:
     element_of_table* elements;
     int current_size_of_table;
     int size_of_table;
private:
    void swap(int i, int j);
    Table& realloc();
public:
    Table() noexcept;//Инициализирующий конструктор(по умолчанию) 1 для таблицы

    Table(element_of_table* initialized_array, int size_of_array) noexcept;//Инициализирующий конструктор 2 для таблицы

    Table(const Table &other) noexcept;//Копирующий конструктор для таблицы

    Table(Table&& other) noexcept;//Конструктор перемещения для таблицы

    ~Table() noexcept { delete[] elements; }//Деструктор для таблицы

    Table& operator = (const Table& other) noexcept;//Перегрузка оператора присваивания копированием

    Table& operator = (Table&& other) noexcept;//Оператор присваивания перемещением для таблицы

    Table& operator += (const element_of_table &elem);//Перегрузка оператора прибавления(делает вставку в таблицу)

    const element_of_table& operator[](int key) const;//Перегрузка оператора квадратные скобки (совершает поиск в таблице)

    friend std::ostream& operator<<(std::ostream &c, const Table &tab) noexcept;//Перегрузка оператора вывода в поток

    int get_current_size_of_table() const noexcept;//Геттер, возвращающий текущий размер таблицы

    int get_size_of_table()const noexcept ;//Геттер, возвращающий размер таблицы

    element_of_table get_elements_at_index(int index) const;//Геттер, возвращающий текущий элемент по индексу

    const element_of_table* get_elements() const;

    std::ostream& print_table(std::ostream& s) const noexcept;//Метод, выводящий таблицу

    const element_of_table& find_element(int key,int& index_delete_element) const;//Метод, возвращающий элемент таблицы, найденный по переданному ключу

    std::string changing_information(int key, std::string name);//Метод, меняющий информацию по введенному ключу

    std::string find_information(int key) const;//Метод, возвращающий информацию, найденную по переданному ключу

    int delete_element(int key);//Метод, выполняющий удаление

    static element_of_table enter_from_the_input_stream() ;//Метод, который позволяет ввести ключ и информацию из потока

    int insert_element(const element_of_table& element);//Метод, выполняющий вставку элемента
};

#endif //LAB2_LIB_LIBRARY_H
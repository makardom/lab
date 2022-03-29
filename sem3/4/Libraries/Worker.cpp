#include "Worker.h"

void Worker::AddNewFriend(Worker *fr) {//не забыть пересчитывать количество оставшихся дней!
    if (Friends.count(fr->getNumber())==0 && Enemies.count(fr->getNumber())==0) {
        Friends[fr->getNumber()] = fr;
        fr->Friends[Number] = this;
    }
    else if (Enemies.count(fr->getNumber())==0)
        throw std::runtime_error("This worker already friends!");
    else
        throw std::runtime_error("This worker is enemy!");
}

void Worker::AddNewEnemy(Worker *en) {//не забыть пересчитывать количество оставшихся дней!
    if (Friends.count(en->getNumber())==0 && Enemies.count(en->getNumber())==0) {
        Enemies[en->getNumber()] = en;
        en->Enemies[Number] = this;
    }
    else if (Friends.count(en->getNumber())==0)
        throw std::runtime_error("This worker already enemy!");
    else
        throw std::runtime_error("This worker is friend!");
}

void Worker::DeleteFriend(int num) {//не забыть пересчитывать количество оставшихся дней!
    if (Friends.count(num)==0)
        throw std::runtime_error("In list absent worker with this number!");
    Friends.erase(num);
}

void Worker::DeleteEnemy(int num) {
    if (Enemies.count(num)==0)
        throw std::runtime_error("In list absent worker with this number!");
    Enemies.erase(num);
}

std::ostream &operator<<(std::ostream &s, Worker *a) {
    s<<"\t"<<"Number: "<<a->Number<<std::endl;
    s<<"\t"<<"Name: "<<a->Name<<std::endl;
    s<<"\t"<<"Age: "<<a->Age<<std::endl;
    s<<"\t"<<"Friends:";
    for (auto it = a->Friends.begin(), end = a->Friends.end(); it!=end; it++){
        s<<" "<<(*it).first;
    }
    s<<std::endl;
    s<<"\t"<<"Enemies:";
    for (auto it = a->Enemies.begin(), end = a->Enemies.end(); it!=end; it++){
        s<<" "<<(*it).first;
    }
    s<<std::endl;
    return s;
}

void Worker::set(int num, const std::string& name, int age) {
    if (num<0)
        throw std::runtime_error("The number must be positive!");
    Number = num;
    Name = name;
    if (age<18)
        throw std::runtime_error("This person cannot be hired!");
    Age = age;
}

bool Worker::operator!=(const Worker *b) {
    if (Number!=b->getNumber())
        return true;
    if (Name!=b->getName())
        return true;
    if (Age!=b->getAge())
        return true;
    return false;
}

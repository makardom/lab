#include "Region.h"
#include <random>
#include <ctime>
#include <utility>

int Region::CheckWorkerByKey(int num){
    if (Workers.count(num)>0)
        return 0;
    return -1;
}

double Region::WorkingOut() {
    std::pair<int, double> perf;
    perf.first = 0; perf.second = 1;
    for (auto it: Workers){
        (it).second->getQuality(perf);
    }
    double Total = perf.first * perf.second;
    if (RForeman== nullptr) {
        int minus = 0;
        for (auto it : Workers) {
            const std::map<int, Worker *> &enemies = (it).second->getEnemies();
            for (auto it1 : enemies) {
                if (CheckWorkerByKey((it1).first) == 0)
                    minus++;
            }
        }
        minus = minus / 2;
        Total -= minus;
        minus = 0;
        for (auto it : Workers) {
            const std::map<int, Worker *> &friends = (it).second->getFriends();
            for (auto it1 : friends) {
                if (CheckWorkerByKey((it1).first) == 0) {
                    const std::map<int, Worker *> &friends2 = (it1).second->getFriends();
                    minus += CountMutualFriend(friends, friends2);
//                    for (auto it2 : friends2)
//                        if (CheckWorkerByKey(it2.first)==0)
//                            minus++;
                }
            }
        }
        minus /= 6;
        Total -= minus;
    }
    if (Total<0)
        return 0;
    return Total;
}

void Region::ChangeVolume(double vol) {
    if (vol<0)
        throw std::runtime_error("Volume is negative!");
    Volume = vol;
    Days = CalculateDays();
}

void Region::AppointForeman(Worker *foreman) {
    auto ptr = dynamic_cast<Foreman *>(foreman);
    ptr->ChangePlot(getNumber());
    foreman = ptr;
    RForeman = foreman;
    Days = CalculateDays();
}

void Region::RemoveWorker(int num) {
    int k = CheckWorkerByKey(num);
    if (k!=-1) {
        Workers.erase(num);
    }
    Days = CalculateDays();
}

int Region::CalculateDays(){
    double work = WorkingOut();
    double time;
    if (work==0){
        time = -1;
    }else
        time = Volume/work;
    int day;
    if (time==-1)
        day = -1;
    else {
        while (time >= 1) {
            time -= 1;
            day += 1;
        }
        if (time > 0) {
            day += 1;
        }
    }
    return day;
}

Region::Region(int num, double vol, std::map<int,Worker *> workers):Number(num), Volume(vol){
    RForeman = nullptr;
    Workers = std::move(workers);
    Days = CalculateDays();
}

void Region::AddWorker(Worker *add) {
    if(CheckWorkerByKey(add->getNumber())==0)
        throw std::runtime_error("This worker already have in this region");
    Workers[add->getNumber()] = add;
    Days = CalculateDays();
}

void Region::WorkDay() {
    Volume -= WorkingOut();
    if (Volume < 0)
        Volume = 0;
    Days = CalculateDays();
}

int Region::CountMutualFriend(const std::map<int, Worker *> &a, const std::map<int, Worker *> &b){
    int k=0;
    for (auto it = a.begin(), end = a.end(); it!=end; it++){
        if(b.find((*it).first)!=b.end() && CheckWorkerByKey((*it).first)==0)
            k++;
    }
    return k;
}

void Region::RemoveForeman() {
    auto ptr = dynamic_cast<Foreman *>(RForeman);
    ptr->ChangePlot(-1);
    RForeman = nullptr;
    Days = CalculateDays();
}

void Region::MakeRelationships() {
    int k=0;
    srand(time(nullptr));
    for (auto it : Workers){
        k++;
    }
    int fr1, fr2, num1 = -1, num2 = -1, num3=-1, num4=-1, en1, en2;
    fr1 = rand() % k;
    fr2 = rand() % k;
    en1 = rand() % k;
    en2 = rand() % k;
    while (true) {
        if (fr1 == fr2) {
            fr2 = (fr2 + rand()) % k;
            continue;
        }
        if (en1==en2){
            en2 = (en2 + rand()) % k;
            continue;
        }
        int i=0;
        for (auto it : Workers){
            if (i == fr1){
                num1 = (it).second->getNumber();
                break;
            }
        }
        i=0;
        for (auto it : Workers){
            if (i == fr2){
                num2 = (it).second->getNumber();
                break;
            }
        }
        i=0;
        for (auto it : Workers){
            if (i == en1){
                num3 = (it).second->getNumber();
                break;
            }
        }
        i=0;
        for (auto it : Workers){
            if (i == en2){
                num4 = (it).second->getNumber();
                break;
            }
        }
        if (num1==-1 || num2 == -1){
            throw std::runtime_error("Not enough to create a relationship");
        }
        const std::map<int, Worker *>& friend1 = Workers[num1]->getFriends();
        const std::map<int, Worker *>& enemies1 = Workers[num1]->getEnemies();
        const std::map<int, Worker *>& friend2 = Workers[num3]->getFriends();
        const std::map<int, Worker *>& enemies2 = Workers[num3]->getEnemies();
        if(friend1.count(num2)==0 && enemies1.count(num2)==0 && friend2.count(num4)==0 && enemies2.count(num4)==0)
            break;
        else
            return;
    }
    Workers[num1]->AddNewFriend(Workers[num2]);
    Workers[num2]->AddNewFriend(Workers[num1]);
    Workers[num3]->AddNewEnemy(Workers[num4]);
    Workers[num4]->AddNewEnemy(Workers[num3]);
    Days = CalculateDays();
}

std::ostream &operator<<(std::ostream &s, Region *a) {
    s<<"Region: "<<a->Number<<std::endl;
    s<<"\tVolume: "<<a->Volume<<std::endl;
    s<<"\tDays: "<<a->Days<<std::endl;
    if (a->RForeman!= nullptr)
        s<<"\tForeman is here"<<std::endl;
    else{
        s<<"\tForeman not in this area"<<std::endl;
    }
    s<<"\tWorkers:"<<std::endl;
    for (auto it : a->Workers){
        s<<"\t"<<(it).first<<std::endl;
    }
    return s;
}

void Region::MakeRemarks() {
    Days = CalculateDays();
}

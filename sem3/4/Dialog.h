#ifndef LAB4_DIALOG_H
#define LAB4_DIALOG_H
#include "Brigade.h"
//#include <string>

template<class T>
int getNum(std::istream &s, T &a){
    while(true) {
        s >> a;
        if (s.good()==1) {
            return 1;
        }
        if (s.eof()==1){
            return -1;
        }
        std::cout<<"repeat enter!";
        s.clear();
        s.ignore(std::numeric_limits<int>::max(), '\n');
    }
}

//std::string get_str(){
//    std::string name;
//    std::getline(std::cin, name);
//    std::string empty;
//    if (std::cin.eof()){
//        return empty;
//    }
//    return name;
//}

int Menu();
int CreateNewEmployee(Brigade &br);
int CreateNewMaster(Brigade &br);
int CreateNewRegion(Brigade &br);
int ChangeOptionOfRegion(Brigade &br);
int AddWorkerInRegion(Brigade &br);
int FireWorkerFromBrigade(Brigade &br);
int DevelopmentOnRegion(Brigade &br);
int CheckPoints(Brigade &br);
int FindProblemRegion(Brigade &br);
int UpToMaster(Brigade &br);
int DeleteRegion(Brigade &br);
int AddFriends(Brigade &br);
int AddEnemy(Brigade &br);
int AppointForeman(Brigade &br);
void SaveInFile(Brigade &br);
void ReadFromFile(Brigade &br);
int DeleteWorkerFromRegion(Brigade &br);

#endif //LAB4_DIALOG_H

#include <fstream>
#include "Dialog.h"


void Dialog(){
    std::cout<<"1. Create new Employee\n"
               "2. Create new Master\n"
               "3. Create new Region\n"
               "4. Change options of regions\n"
               "5. Add worker in region\n"
               "6. Delete worker from region\n"
               "7. Fire Worker\n"
               "8. Development on the site\n"
               "9. Have all points done?\n"
               "10. Most problem region\n"
               "11. Upgrade to Master\n"
               "12. Delete region\n"
               "13. Add friend\n"
               "14. Add enemy\n"
               "15. Appoint foreman in other region\n"
               "16. Print brigade\n"
               "17. Pass day\n"
               "18. Save in file\n"
               "19. Read from file\n"
               "0. Exit\n";
    std::cout<<"Enter your choice:"<<std::endl;
}

int Menu(){
    Brigade brigade;
    auto *foreman = new Foreman;
    std::cout<<"Enter name of foreman:"<<std::endl;
    std::string name;
    std::getline(std::cin, name);
    std::cout<<"Enter age:"<<std::endl;
    int age;
    if (getNum(std::cin, age)==-1)
        return -1;
    foreman->set(0, name, age);
    std::cout<<"Age: "<<age<<std::endl;
    Worker *forem = foreman;
    brigade.AddForeman(forem);
    int flag = 1;
    while(flag){
        Dialog();
        int choice;
        if (getNum(std::cin, choice)==-1)
            return -1;
        if (choice<0 || choice>19) {
            std::cout<<"You enter wrong number"<<std::endl;
            continue;
        }
        switch (choice) {
            case 1:
                if(CreateNewEmployee(brigade) == -1)
                    return -1;
                break;
            case 2:
                if(CreateNewMaster(brigade)==-1)
                    return -1;
                break;
            case 3:
                if (CreateNewRegion(brigade)==-1)
                    return -1;
                break;
            case 4:
                if (ChangeOptionOfRegion(brigade)==-1)
                    return -1;
                break;
            case 5:
                if (AddWorkerInRegion(brigade)==-1)
                    return -1;
                break;
            case 6:
                if (DeleteWorkerFromRegion(brigade)==-1)
                    return -1;
                break;
            case 7:
                if (FireWorkerFromBrigade(brigade)==-1)
                    return -1;
                break;
            case 8:
                if (DevelopmentOnRegion(brigade)==-1)
                    return -1;
                break;
            case 9:
                if (CheckPoints(brigade)==-1)
                    return -1;
                break;
            case 10:
                if (FindProblemRegion(brigade)==-1)
                    return -1;
                break;
            case 11:
                if (UpToMaster(brigade)==-1)
                    return -1;
                break;
            case 12:
                if (DeleteRegion(brigade)==-1)
                    return -1;
                break;
            case 13:
                if (AddFriends(brigade)==-1)
                    return -1;
                break;
            case 14:
                if (AddEnemy(brigade)==-1)
                    return -1;
                break;
            case 15:
                if (AppointForeman(brigade)==-1)
                    return -1;
                break;
            case 16:
                std::cout<<brigade<<std::endl;
                break;
            case 17:
                try{
                    brigade.PassDay();
                }catch (std::runtime_error &rt){
                    std::cout<<rt.what()<<std::endl;
                }
                break;
            case 18:
                SaveInFile(brigade);
                break;
            case 19:
                ReadFromFile(brigade);
                break;
            case 0:
               flag =0;
                break;
        }
    }
    brigade.ClearAll();
    delete foreman;
    return 0;
}

int CreateNewEmployee(Brigade &br){
    std::cin.ignore(32767, '\n');
    std::cout<<"Enter name of employee:"<<std::endl;
    std::string name;
    std::getline(std::cin, name);
    std::cout<<"Enter age:"<<std::endl;
    int age;
    if (getNum(std::cin, age)==-1)
        return -1;
    std::cin.ignore(32767, '\n');
    std::cout<<"Enter unique number:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    std::cin.ignore(32767, '\n');
    std::cout<<"Enter quality of this employee:"<<std::endl;
    int qual;
    if (getNum(std::cin, qual)==-1)
        return -1;
    std::cin.ignore(32767, '\n');
    auto *worker = new Employee;
    try {
        worker->set(num, name, age);
        worker->ChangeQuality(qual);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
        return 0;
    }
    Worker *add = worker;
    try{
        br.AddWorker(add);
    }catch (std::exception &rt){
        std::cout<<"Worker with this number already have!"<<std::endl;
    }
    return 0;
}

int CreateNewMaster(Brigade &br){
    std::cin.ignore(32767, '\n');
    std::cout<<"Enter name of master:"<<std::endl;
    std::string name;
    std::getline(std::cin, name);
    std::cout<<"Enter age:"<<std::endl;
    int age;
    if (getNum(std::cin, age)==-1)
        return -1;
    std::cout<<"Enter unique number:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    std::cout<<"Enter quality of this master:"<<std::endl;
    double qual;
    if (getNum(std::cin, qual)==-1)
        return -1;
    auto *worker = new Master;
    try {
        worker->set(num, name, age);
        worker->ChangeQuality(qual);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
        return 0;
    }
    Worker *add = worker;
    try{
        br.AddWorker(add);
    }catch (std::exception &rt){
        std::cout<<"Worker with this number already have!"<<std::endl;
    }
    return 0;
}

int CreateNewRegion(Brigade &br){
    std::cout<<"Enter unique number:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    auto *region = new Region(num);
    std::cout << "Enter volume:" << std::endl;
    int vol;
    if (getNum(std::cin, vol) == -1)
        return -1;
    try{
        region->ChangeVolume(vol);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
        return 0;
    }
    try{
        br.AddNewRegion(region);
    }catch (std::exception &rt){
        std::cout<<"Region with this number already have"<<std::endl;
    }
    return 0;
}

int ChangeOptionOfRegion(Brigade &br){
    std::cout<<"Enter number of region which you want to change:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    std::cout<<"Enter new volume:"<<std::endl;
    double vol;
    if (getNum(std::cin, vol)==-1)
        return -1;
    try{
        if (br.ChangeInRegion(vol, num)==-1)
            std::cout<<"Region with this number is absent!"<<std::endl;
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int AddWorkerInRegion(Brigade &br){
    std::cout<<"Enter number of worker which you want to appoint:"<<std::endl;
    int numw;
    if (getNum(std::cin, numw)==-1)
        return -1;
    std::cout<<"Enter number of region:"<<std::endl;
    int numr;
    if (getNum(std::cin, numr)==-1)
        return -1;
    try {
        br.AppointWorkerInRegion(numw, numr);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int FireWorkerFromBrigade(Brigade &br){
    std::cout<<"Enter number of worker which you want to fire:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    try{
        br.FireWorker(num);
    }catch (std::exception &ex){
        std::cout<<"In brigade worker with this number is absent!"<<std::endl;
    }
    return 0;
}

int DevelopmentOnRegion(Brigade &br){
    std::cout<<"Enter number of plot, where you want know development:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    try{
        std::cout<<"Performance data = "<<br.PerformanceData(num)<<std::endl;
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int CheckPoints(Brigade &br){
        if (br.CompleteWork()==1)
            std::cout<<"All tasks will be completed on this day"<<std::endl;
        else
            std::cout<<"All tasks won't be completed on this day"<<std::endl;
    return 0;
}

int FindProblemRegion(Brigade &br){
    try{
        std::cout<<"Most problem region have number: "<<br.MostProblem()<<std::endl;
    } catch (std::runtime_error &rt) {
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int UpToMaster(Brigade &br){
    std::cout<<"Enter number of employee:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    std::cout<<"Enter new quality of this master:"<<std::endl;
    double qual;
    if (getNum(std::cin, qual)==-1)
        return -1;
    try{
        br.UpgradeToMaster(num, qual);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int DeleteRegion(Brigade &br){
    std::cout<<"Enter number of plot you want delete:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    try{
        br.DeleteRegion(num);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int AddFriends(Brigade &br){
    std::cout<<"Enter number of worker:"<<std::endl;
    int num1;
    if (getNum(std::cin, num1)==-1)
        return -1;
    std::cout<<"Enter number of new friend:"<<std::endl;
    int num2;
    if (getNum(std::cin, num2)==-1)
        return -1;
    try{
        br.MakeANewFriends(num1, num2);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int AddEnemy(Brigade &br){
    std::cout<<"Enter number of worker:"<<std::endl;
    int num1;
    if (getNum(std::cin, num1)==-1)
        return -1;
    std::cout<<"Enter number of new enemy:"<<std::endl;
    int num2;
    if (getNum(std::cin, num2)==-1)
        return -1;
    try{
        br.MakeANewEnemy(num1, num2);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

int AppointForeman(Brigade &br){
    std::cout<<"Enter number of region, where you want appoint foreman:"<<std::endl;
    int num;
    if (getNum(std::cin, num)==-1)
        return -1;
    try{
        br.AppointForeman(num);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}

void SaveInFile(Brigade &br){
    std::cin.ignore(32767, '\n');
    std::ofstream ff;
    std::string file;
    std::cout<<"Enter file's name to record table:"<<std::endl;
    std::getline(std::cin, file);
    ff.open(file);
    if (!ff.is_open()){
        std::cout<<"File is not opened"<<std::endl;
        return;
    }
    br.RecordFile(ff);
    ff.close();
}

void ReadFromFile(Brigade &br){
    std::cin.ignore(32767, '\n');
    std::ifstream ff;
    std::string file;
    std::cout<<"Enter file's name to read table:"<<std::endl;
    std::getline(std::cin, file);
    ff.open(file);
    if (!ff.is_open()){
        std::cout<<"File is not opened"<<std::endl;
        return;
    }
    br.ReadFromFile(ff);
    ff.close();
}

int DeleteWorkerFromRegion(Brigade &br){
    std::cout<<"Enter number of worker which you want to appoint:"<<std::endl;
    int numw;
    if (getNum(std::cin, numw)==-1)
        return -1;
    std::cout<<"Enter number of region:"<<std::endl;
    int numr;
    if (getNum(std::cin, numr)==-1)
        return -1;
    try {
        br.DeleteFromRegion(numw, numr);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }
    return 0;
}
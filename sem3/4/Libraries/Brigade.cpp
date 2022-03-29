#include "Brigade.h"

void Brigade::AddWorker(Worker *adder) {
    if (CheckWorkerByKey(adder->getNumber())==0)
        throw std::exception();
    Workers.insert(adder->getNumber(), adder);
//    Workers[adder->getNumber()] = adder;
}

void Brigade::FireWorker(int num) {
    int k = CheckWorkerByKey(num);
    if (k==-1)
        throw std::exception();
    for (auto it : Regions){
        (it).second->RemoveWorker(num);
    }
    Workers.RemoveElem(num);
}

int Brigade::CheckWorkerByKey(int num) {
    if (Workers.count(Workers.TakeRoot(), num)>0)
        return 0;
    return -1;
}

int Brigade::CheckRegionByKey(int num) {
    if (Regions.count(num)>0)
        return 0;
    return -1;
}


void Brigade::AddNewRegion(Region *add) {
    if (CheckRegionByKey(add->getNumber())==0)
        throw std::exception();
//    Regions.push_back(add);
    Regions[add->getNumber()]=add;
}

void Brigade::DeleteRegion(int num) {
    int k = CheckRegionByKey(num);
    if (k==-1)
        throw std::runtime_error("Region with this number is absent");
    delete Regions[num];
    Regions.erase(num);
}

double Brigade::PerformanceData(int num) const {
    double total = -1;
    total = Regions.at(num)->WorkingOut();
    if (total == -1){
        throw std::runtime_error("Region with this number is absent!");
    }else if (total==0){
        throw std::runtime_error("No employees in this region!");
    }
    return total;
}

int Brigade::MostProblem() const {
    int num, MaxDay=0;
    double vol = 0;
    for (auto it : Regions){
        if ((it).second->getDays() > MaxDay || (it).second->getDays()==-1){
            if ((it).second->getDays()==-1 && (it).second->getVolume()>vol){
                num = (it).first;
                MaxDay = INT_MAX;
                vol = (it).second->getVolume();
            }else{
                num = (it).first;
                MaxDay = (it).second->getDays();
            }
        }
    }
    if(MaxDay == 0){
        throw std::runtime_error("Work on all regions is completed");
    }
    return num;
}

void Brigade::UpgradeToMaster(int num, double qual) {//!!!!!
    if (CheckWorkerByKey(num)==-1)
        throw std::runtime_error("No anyone worker with this number");
    if (typeid(*Workers[num])== typeid(Master))
        throw std::runtime_error("This worker already is master");
    auto now = dynamic_cast<Employee *>(Workers[num]);
    auto *master = new Master;
    master->set(now->getNumber(), now->getName(), now->getAge());
    if(master->ChangeQuality(qual)==-1)
        throw std::runtime_error("Entered quality is wrong!");
    master->CopyFrEn(now->getFriends(), now->getEnemies());
    Worker * mast = master;
    Workers.RemoveElem(mast->getNumber());
    Workers.insert(mast->getNumber(), mast);
//    Workers[num] = master;
    for (auto it : Regions){
        if ((it).second->CheckWorkerByKey(num)==0) {
            (it).second->RemoveWorker(num);
            (it).second->AddWorker(Workers[num]);
        }
        (it).second->MakeRemarks();
    }
}

void Brigade::AddForeman(Worker *a) {
    if (BForeman!= nullptr)
        throw std::runtime_error("In brigade already have foreman!");
    BForeman = a;
}

void Brigade::PassDay() {
    for (auto it : Regions){
        (it).second->WorkDay();
        (it).second->MakeRelationships();
    }
}

std::ostream &operator<<(std::ostream &s, Brigade &br) {
    s<<"Brigade:"<<std::endl;
    if (br.BForeman== nullptr)
        s<<"No Workers in brigade"<<std::endl;
    else{
        br.BForeman->PrintClass(s);
        s<<br.BForeman;
        for (auto it=br.Workers.begin(), end = br.Workers.end(); it!=end; it++){
            (*it).info->PrintClass(s);
            s<<(*it).info;
        }
        for (auto it=br.Regions.begin(), end = br.Regions.end(); it!=end; it++){
            s<<(*it).second;
        }
    }
    return s;
}

int Brigade::CompleteWork() const{
    int flag = 0;
    for (auto it : Regions){
        if ((it).second->getDays()>1)
            flag =1;
    }
    if (flag == 0)
        return 1;
    else
        return 0;
}

int Brigade::ChangeInRegion(double vol, int num) {
    int flag=0;
    for (auto it : Regions){
        if ((it).second->getNumber() == num){
            (it).second->ChangeVolume(vol);
            flag =1;
        }
    }
    if (flag)
        return 0;
    return -1;
}

void Brigade::AppointWorkerInRegion(int numw, int numr) {
    for (auto it : Workers){
        if ((it).info->getNumber()==numw){
            for (auto it1 : Regions){
                (it1).second->RemoveWorker(numw);
                if ((it1).second->getNumber()==numr){
                    (it1).second->AddWorker((it).info);
                }
            }
        }
    }
}

int Brigade::MakeANewFriends(int num1, int num2) {
    if (CheckWorkerByKey(num1)==-1)
        throw std::runtime_error("Worker with first number is absent!");
    if (CheckWorkerByKey(num2)==-1)
        throw std::runtime_error("Worker with second number is absent!");
    Workers[num1]->AddNewFriend(Workers[num2]);
    for (auto it : Regions){
        (it).second->MakeRemarks();
    }
    return 0;
}

int Brigade::MakeANewEnemy(int num1, int num2) {
    if (CheckWorkerByKey(num1)==-1)
        throw std::runtime_error("Worker with first number is absent!");
    if (CheckWorkerByKey(num2)==-1)
        throw std::runtime_error("Worker with second number is absent!");
    Workers[num1]->AddNewEnemy(Workers[num2]);
    for (auto it : Regions){
        (it).second->MakeRemarks();
    }
    return 0;
}

int Brigade::AppointForeman(int num) {
    if (CheckRegionByKey(num)==-1)
        throw std::runtime_error("Region with this key is absent!");
    auto foreman = dynamic_cast<Foreman *>(BForeman);
    for (auto it : Regions){
        if (foreman->getPlotNumber()==(it).second->getNumber())
            (it).second->RemoveForeman();
    }
    for (auto it : Regions){
        if ((it).first == num)
            (it).second->AppointForeman(BForeman);
    }
    return 0;
}

void Brigade::RecordFile(std::ofstream &f) {
    f<<BForeman->getName()<<std::endl<<BForeman->getAge()<<" ";
    auto ptr = dynamic_cast<Foreman *>(BForeman);
    f<<ptr->getPlotNumber()<<std::endl;
    int kol = 0;
    for (auto it : Workers){
        kol ++;
    }
    f<<kol<<std::endl;
    for (auto it : Workers){
        f<<it.info->getName()<<std::endl;
        if (typeid(*it.info)==typeid(Master)){
            f<<"1"<<std::endl;
        }else{
            f<<"0"<<std::endl;
        }
        f<<it.info->getNumber()<<" "<<it.info->getAge()<<" ";
        std::pair<int, double> pair;
        pair.first = 0; pair.second = 1;
        it.info->getQuality(pair);
        if (pair.first==0)
            f<<pair.second<<std::endl;
        else
            f<<pair.first<<std::endl;
    }
//    for (auto it : Workers){
//        for (auto it1 : it.info->getFriends()){
//            f<<it1.first<<" ";
//        }
//        f<<std::endl;
//        for (auto it1 : it.info->getEnemies()){
//            f<<it1.first<<" ";
//        }
//        f<<std::endl;
//    }
    kol = 0;
    for (auto it : Regions){
        kol ++;
    }
    f<<kol<<std::endl;
    for (auto it : Regions){
        f<<it.second->getNumber()<<" "<<it.second->getVolume()<<std::endl;
        if (it.second->getForeman()== nullptr)
            f<<0<<std::endl;
        else
            f<<1<<std::endl;
        int kol1=0;
        for (auto it1 : it.second->getWorkers()){
            kol1++;
        }
        f<<kol1<<std::endl;
        for (auto it1 : it.second->getWorkers()){
            f<<it1.first<<" ";
        }
        f<<std::endl;
    }
}

void Brigade::ClearAll() {
    int kol = 0;
    for (auto it : Workers)
        kol ++;
    int num[kol];
    int i=0;
    for (auto it : Workers){
        num[i] = it.key;
        i++;
    }
    for (i=0; i<kol; i++){
        FireWorker(num[i]);
    }
    kol = 0;
    for (auto it : Regions)
        kol++;
    int reg[kol];
    i = 0;
    for (auto it : Regions){
        reg[i] = it.first;
        i++;
    }
    for (i=0; i<kol; i++){
        DeleteRegion(reg[i]);
    }
}

void Brigade::ReadFromFile(std::ifstream &f) {
    std::string name;
    int age, plot;
    std::getline(f, name);
    f>>age>>plot;
    f.ignore(std::numeric_limits<int>::max(), '\n');
    BForeman->set(0, name, age);
    auto ptr = dynamic_cast<Foreman *>(BForeman);
    ptr->ChangePlot(plot);
    int kol, qualadd, num, who;
    double qualmulti;
    f>>kol;
    f.ignore(std::numeric_limits<int>::max(), '\n');
    for (int i=0; i<kol; i++){
        std::getline(f, name);
        f>>who;
        f.ignore(std::numeric_limits<int>::max(), '\n');
        if (who==0) {
            f >> num >> age >> qualadd;
            auto *empl = new Employee;
            empl->set(num, name, age);
            empl->ChangeQuality(qualadd);
            Worker *add = empl;
            AddWorker(add);
        }
        else {
            f >> num >> age >> qualmulti;
            auto *mast = new Master;
            mast->set(num, name, age);
            mast->ChangeQuality(qualmulti);
            Worker *add = mast;
            AddWorker(add);
        }
        f.ignore(std::numeric_limits<int>::max(), '\n');
    }
    f>>kol;
    for(int i=0; i<kol; i++){
        int fr, workkol;
        double vol;
        f>>num>>vol;
        f.ignore(std::numeric_limits<int>::max(), '\n');
        f>>fr;
        f.ignore(std::numeric_limits<int>::max(), '\n');
        f>>workkol;
        f.ignore(std::numeric_limits<int>::max(), '\n');
        auto *reg = new Region(num);
        reg->ChangeVolume(vol);
        for (int j=0; j<workkol; j++){
            int worknum;
            f>>worknum;
            reg->AddWorker(Workers[worknum]);
        }
        AddNewRegion(reg);
        f.ignore(std::numeric_limits<int>::max(), '\n');
    }
}

void Brigade::DeleteFromRegion(int numw, int numr) {
    for (auto it : Regions){
        if (it.first == numr)
            (it).second->RemoveWorker(numw);
    }
}


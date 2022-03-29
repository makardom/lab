#include "Master.h"

#include <utility>

void Master::getQuality(std::pair<int, double> &perf) const {
    if (QualityMulti!=0)
        perf.second *= QualityMulti;
}

int Master::ChangeQuality(double change) {
    if (change>5 || change<1)
        return -1;
    QualityMulti = change;
    return 0;
}

Master::Master(Employee *a): Worker(a->getNumber(), a->getName(), a->getAge()) {
    QualityMulti = 0;
    Friends = a->getFriends();
    Enemies = a->getEnemies();
}

void Master::PrintClass(std::ostream &s) const {
    s<<"Master:"<<std::endl;
    s<<"Quality: "<<QualityMulti<<std::endl;
}

void Master::CopyFrEn(std::map<int, Worker *> fr, std::map<int, Worker *> en) {
    Friends = std::move(fr);
    Enemies = std::move(en);
}

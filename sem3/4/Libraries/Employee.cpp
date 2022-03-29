#include "Employee.h"

void Employee::getQuality(std::pair<int, double> &perf) const {
    perf.first += QualityAdd;
}

int Employee::ChangeQuality(int change) {
    if (change>10 || change<1)
        return -1;
    QualityAdd = change;
    return 0;
}

void Employee::PrintClass(std::ostream &s) const {
    s<<"Employee:"<<std::endl;
    s<<"Quality: "<<QualityAdd<<std::endl;
}

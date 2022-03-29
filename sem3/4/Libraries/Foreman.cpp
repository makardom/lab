#include "Foreman.h"

void Foreman::ChangePlot(int next) {
    PlotNumber = next;
}

void Foreman::PrintClass(std::ostream &s) const {
    s<<"Foreman:"<<std::endl;
    s<<"\tPlot number: "<<PlotNumber<<std::endl;
}

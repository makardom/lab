#ifndef EXTERNAL_DIALOG_H
#define EXTERNAL_DIALOG_H
#include "library.h"

struct Info{
    std::string first_name;
    int visit;
    int *score;
};

int menu();
int EnterNewPupil(Table &tab);
int AddVisit(Table &tab);
int AddNewGrade(Table &tab);
int PrintByKey(Table &tab);
int DeleteStudentByKey(Table &tab);
int AverageGrade(Table &tab);
int RecordInFile(Table &tab);
int ReadFromFile(Table &tab);

#endif //EXTERNAL_DIALOG_H

#include "External.h"

#include <utility>


int *ArrayOfGrades(std::string str){
    int kol = 0;
    std::string str1 = std::move(str);
    for (char i : str1){
        if (i==' ')
            kol++;
    }
    int *numbs = new int [kol+1];
    for (int i=0; i<kol; i++){
        int j=0;
        while (str1[j]!=' '){
            j++;
        }
        std::string dop;
        dop.assign(str1, 0, j);
        numbs[i] = std::stoi(dop);
        str1 = str1.substr(j+1);
    }
    numbs[kol]=0;
    return numbs;
}

Info *TakeInfoFromStr(std::string str){
    Info *pupil;
    pupil = new Info;
    int k=0;
    for (int i=0; i<str.length(); i++){
        if (str[i]==' '){
            k=i+1;
            break;
        }
    }
    pupil->first_name.assign(str, 0, k-1);
    std::string dop = str.substr(k);
    for (int i=0; i<dop.length(); i++){
        if (dop[i]==' '){
            k=i;
            break;
        }
    }
    std::string num;
    num.assign(dop, 0, k);
    pupil->visit = std::stoi(num);
    if (k+1==dop.length()){
        pupil->score = nullptr;
    }else{
        dop = dop.substr(k+1);
        pupil->score = ArrayOfGrades(dop);
    }
    return pupil;
}
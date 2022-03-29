#include <cstring>
#include "Dialog.h"
#include "External.h"
#include <fstream>

void Funcs(){
    std::cout<<"1. Enter New Student\n"<<"2. Add visit\n"<<"3. Add grade\n"<<"4. Print all students\n"<<"5. Search student(by key)\n"<<"6. Calculate average grade\n"<<"7. Delete student from table\n"<<"8. Record in file\n"<<"9. Read from file\n"<<"0. Exit\n";
    std::cout<<"Enter choice:"<<std::endl;
}

int menu(){
    Table tab;
    int choice=-1;
    while(choice!=0) {
        Funcs();
        try {
            getNum(choice);
        } catch (std::runtime_error &rt) {
            std::cout << rt.what() << std::endl;
            return -1;
        }
        if (choice<0 || choice>9){
            std::cout<<"Your choice is wrong!"<<std::endl;
            continue;
        }
        if (choice==0){
            std::cout<<"End."<<std::endl;
            return 0;
        }
        switch (choice) {
            case 1:
                if (EnterNewPupil(tab)==-1)
                    return -1;
                break;
            case 2:
                if (AddVisit(tab)==-1)
                    return -1;
                break;
            case 3:
                if (AddNewGrade(tab)==-1)
                    return -1;
                break;
            case 4:
                tab.print_table(std::cout);
                break;
            case 5:
                if (PrintByKey(tab)==-1)
                    return -1;
                break;
            case 6:
                if (AverageGrade(tab)==-1)
                    return -1;
                break;
            case 7:
                if (DeleteStudentByKey(tab)==-1)
                    return -1;
                break;
            case 8:
                if(RecordInFile(tab)==-1)
                    return -1;
                break;
            case 9:
                if (ReadFromFile(tab)==-1)
                    return -1;
                break;
        }
    }
    return 0;
}

int EnterNewPupil(Table &tab){
    element_of_table Elem;
    std::cout<<"Enter key:"<<std::endl;
    int key;
    try{
        getNum(key);
        Elem.set_key(key);
        std::cout<<"Enter Last name:"<<std::endl;
        Info *pupil;
        pupil = new Info;
        pupil->first_name = get_str();
        pupil->visit = 0;
        std::string firstname, visit, total;
        firstname = pupil->first_name;
        visit = std::to_string(pupil->visit);
        total+=firstname;
        total+=" ";
        total+=visit;
        total += " ";
        Elem.set_name(total);
//        tab.insert_element(Elem);
        tab+=Elem;
        delete pupil;
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    return 0;
}

int AddVisit(Table &tab){
    try{
        std::cout << "Enter student's key:" << std::endl;
        int key;
        getNum(key);
        std::string str = tab.find_information(key);
        int k=0;
        for (int i=0; i<str.length(); i++){
            if (str[i]==' '){
                k=i+1;
                break;
            }
        }
        std::string dop = str.substr(k);
        int m = 0;
        for (int i=0; i<dop.length(); i++){
            if (dop[i]==' '){
                m=i;
                break;
            }
        }
        char *num = new char[m+1];
        std::size_t length = dop.copy(num, m, 0);
        num[length] = '\0';
        std::string str1(num);
        int visit = std::stoi(str1);
        int v = visit;
        m=0;
        if (v==0)
            m=1;
        while (v>0){
            v/=10;
            m++;
        }
        visit +=1;
        str1 = std::to_string(visit);
        delete []num;
        str1+=" ";
        str.replace(k,m+1,str1);
        tab.changing_information(key, str);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }catch(std::exception &rt) {
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    return 0;
}

int AddNewGrade(Table &tab) {
    try {
        std::cout << "Enter student's key:" << std::endl;
        int key;
        getNum(key);
        std::cout << "Enter grade from 1 to 10:" << std::endl;
        int grade;
        getNum(grade);
        if (grade > 10 || grade < 1) {
            std::cout << "Entered grade is wrong" << std::endl;
            return -1;
        }
        std::string gr = std::to_string(grade);
        std::string str = tab.find_information(key);
        str += gr;
        str += " ";
        tab.changing_information(key, str);
    } catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    return 0;
}

int PrintByKey(Table &tab){
    std::cout<<"Enter key, to find student:"<<std::endl;
    try{
        int key;
        getNum(key);
        std::string str;
        str = tab.find_information(key);
        Info *pupil = TakeInfoFromStr(str);
        std::cout<<"Last name: "<<pupil->first_name<<" Visits: "<<pupil->visit;
        int k=0;
        std::cout<<" Grades:";
        while (pupil->score!=nullptr && pupil->score[k]!= 0){
            std::cout<<" "<<pupil->score[k];
            k++;
        }
        std::cout<<std::endl;
        delete [] pupil->score;
        delete pupil;
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    return 0;
}

int DeleteStudentByKey(Table &tab){
    std::cout<<"Enter key, to delete student:"<<std::endl;
    try{
        int key;
        getNum(key);
        tab.delete_element(key);
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    return 0;
}

int AverageGrade(Table &tab){
    std::cout<<"Enter key, to find student:"<<std::endl;
    try{
        int key;
        getNum(key);
        std::string str;
        str = tab.find_information(key);
        Info *pupil = TakeInfoFromStr(str);
        int k=0; int sum = 0;
        while(pupil->score!= nullptr && pupil->score[k]!=0){
            sum+=pupil->score[k];
            k++;
        }
        double average=0;
        if (k!=0){
            average=(double)sum/k;
        }
        std::cout<<"Last name: "<<pupil->first_name<<" Average grade: "<<average<<std::endl;
        if (sum>k*6){
            std::cout<<"Student have good overall score"<<std::endl;
        }else{
            std::cout<<"The student should try better!!!"<<std::endl;
        }
        delete []pupil->score;
        delete pupil;
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    return 0;
}

int RecordInFile(Table &tab){
    std::ofstream ff;
    std::string file;
    std::cout<<"Enter file's name to record table:"<<std::endl;
    try{
        file = get_str();
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    ff.open(file);
    if (!ff.is_open()){
        std::cout<<"File is not opened"<<std::endl;
        return 1;
    }
    for (int i=0; i<tab.get_current_size_of_table(); i++){
        ff<<tab.get_elements_at_index(i).get_key()<<std::endl;
        ff<<tab.get_elements_at_index(i).get_name()<<std::endl;
    }
    ff.close();
    return 0;
}

int ReadFromFile(Table &tab){
    std::ifstream ff;
    std::string file;
    std::cout<<"Enter file's name to read table:"<<std::endl;
    try{
        file = get_str();
    }catch (std::exception &rt){
        std::cout<<"EOF"<<std::endl;
        return -1;
    }
    ff.open(file);
    if (!ff.is_open()){
        std::cout<<"File is not opened"<<std::endl;
        return 1;
    }
    try {
        while (!ff.eof()) {
            element_of_table Elem;
            int key;
            std::string str;
            ff >> key;
            ff.ignore();
            std::getline(ff, str, '\n');
            Elem.set_key(key);
            Elem.set_name(str);
            tab.insert_element(Elem);
        }
    }catch (std::runtime_error &rt){
        std::cout<<rt.what()<<std::endl;
        return 0;
    }
    return 0;
}
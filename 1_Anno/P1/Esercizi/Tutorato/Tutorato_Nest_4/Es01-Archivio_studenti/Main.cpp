#include<iostream>
#include<cstring>
using namespace std;

#define MAX_STUDENTS 100
#define DIM 31

struct Student{
    char nome[DIM];
    char cognome[DIM];
    unsigned int id;
};

struct Archive{
    Student * studentsBySurname;
    Student * studentsById;
    unsigned int num_studenti;
};

bool addStudent(Student * students, Archive * archive);
void printArchive(Archive * archive);

int main() {
    Student students[]={
        {"Mario", "E", 4},
        {"Luigi", "B", 1},
        {"Luigi", "D", 2},
        {"Luigi", "C", 3}
    };
    Student studentsById[MAX_STUDENTS];
    Student studentsBySurname[MAX_STUDENTS];
    Archive archive = {studentsById, studentsBySurname, 0};

    for(int i = 0; i < sizeof(students) / sizeof(students[0]); i++){
        if(addStudent(&students[i], &archive)){
            archive.num_studenti++;
            cout<<"Student added"<<endl;
        }else{
            cout<<"Student not added"<<endl;
        }
    }

    printArchive(&archive);
    return (0);
}

bool addStudent(Student * students, Archive * archive){
    int i=0;
    bool trovato=false;
    while(i<(archive->num_studenti) && (!trovato)){
        if((students->id)<(archive->studentsById[i].id)){
            trovato=true;
        }else{
            i++;
        }
        if(i >= MAX_STUDENTS-1){
            return false;
        }
    }
    for(int g=(archive->num_studenti); g>i; g--){
        archive->studentsById[g]=archive->studentsById[g-1];
    }

    archive->studentsById[i] = *students;
    return true;
}

void printArchive(Archive * archive){
    for(int i=0; i<(archive->num_studenti); i++){
        cout<<archive->studentsById[i].id<<" ";
    }
    cout<<endl;
}
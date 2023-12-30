#ifndef VOLUMESYS_H
#define VOLUMESYS_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Utils.h"
#include "Student.h"
#include "Teacher.h"


using namespace std;

class VolumeSys {
private:
    uint64_t volumeSize;
    uint16_t ArrTeacherSize;
    uint16_t ArrStudentSize;
    uint16_t passsize;
    string password;
public:
    VolumeSys();
    VolumeSys(uint64_t volumeSize);
    void setPassword(string pass);
    void ReadVolume(string fileName);
    void WriteVolume(ofstream& file);
    string getPass() {
        return this->password;
    }
    uint16_t getPasssize() {
        return this->passsize;
    }

    void AddStudent(Student& student, string fileName);
    void ReadStudentList(string fileName);
    void DeleteOrRestoreStudent(string fileName, const char* studentId, bool isDeleted);

    void AddTeacher(Teacher& teacher, string fileName);
    void UpdateTeacherSize(string fileName);
    void ReadTeacherList(string fileName);
    void DeleteOrRestoreTeacher(string fileName, const char* teacherId, bool isDeleted);
};

#endif
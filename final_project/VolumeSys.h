#define _CRT_SECURE_NO_WARNINGS
#ifndef VOLUMESYS_H
#define VOLUMESYS_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Utils.h"
#include "Student.h"
#include "Teacher.h"
#include "Crypto.h"

using namespace std;

class VolumeSys {
private:
    uint64_t volumeSize;
    uint16_t ArrTeacherSize;
    uint16_t ArrStudentSize;
    char password[127];

public:
    VolumeSys();
    VolumeSys(uint64_t volumeSize);
    
    void ReadVolume(string fileName);
    void WriteVolume(ofstream& file);

    void AddStudent(Student& student, string fileName);
    void ReadStudentList(string fileName);
    void DeleteOrRestoreStudent(string fileName, const char* studentId, bool isDeleted);

    void AddTeacher(Teacher& teacher, string fileName);
    void UpdateTeacherSize(string fileName);
    void ReadTeacherList(string fileName);
    void DeleteOrRestoreTeacher(string fileName, const char* teacherId, bool isDeleted);

    void DeleteStudentPermanently(string fileName, const char* studentId);
    void DeleteTeacherPermanently(string fileName, const char* teacherId);

    void UpdatePassword(string fileName);

    char* getPass() {
        return this->password;
    }

    uint64_t getVolumeSize() {
        return this->volumeSize;
    }

    void setPassword(string pass);

    void ResetPassword() {
        memset(this->password, '\0', 65);
    }
};

#endif
#pragma once
#include <iostream>
#include <string>
#include "SHA256.h"
#include "Main.h"
using namespace std;


class VolumeSys{
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
    void ReadVolume(fstream& file);
    void WriteVolume(fstream& file);
    string getPass() {
        return this->password;
    }
    uint16_t getPasssize() {
        return this->passsize;
    }
    uint64_t getVolume() {
        return this->volumeSize;
    }
};


#include "VolumeSys.h"


VolumeSys::VolumeSys(uint64_t volumeSize) {
    this->volumeSize = volumeSize;
 
    this->ArrTeacherSize = 0;
    this->ArrStudentSize = 0;
    
    this->passsize = 0;
    this->password = "";
}
void VolumeSys::setPassword(string pass) {
    this->password = HashPassFuc(pass);
    this->passsize = this->password.length();
}

void VolumeSys::ReadVolume(fstream& file)
{
    file.read((char*)&this->volumeSize, sizeof(this->volumeSize));
    file.read((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
    file.read((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
    file.read((char*)&this->passsize, sizeof(this->passsize));
    this->password.resize(this->passsize);
    file.read((char*)this->password.c_str(), this->passsize);
    cout << "Read Volume system successfully" << endl;
}

void VolumeSys::WriteVolume(fstream& file)
{
    file.write((char*)&this->volumeSize, sizeof(this->volumeSize));
    file.write((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
    file.write((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
    file.write((char*)&this->passsize, sizeof(this->passsize));
    this->password.resize(this->passsize);
    file.write((char*)this->password.c_str(), this->passsize);
    cout << "Write Volume system successfully" << endl;
}
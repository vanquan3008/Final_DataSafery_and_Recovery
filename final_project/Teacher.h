#define _CRT_SECURE_NO_WARNINGS
#ifndef TEACHER_H
#define TEACHER_H
#include<iostream>
#include "Crypto.h"

using namespace std;

class Teacher
{
private:	
	char id[9];
	char name[256];
	char age[3];
	char phone[127];
	char cccd[127];
	/*char CreateAt[8];
	char timeAt[6];
	char dateDelete[8];
	char timeDelete[6];*/
	bool isDeleted;
public:
	void InputTeacher();

	char* getId();
	char* getName();
	char* getAge();
	char* getPhone();
	char* getCCCD();
	bool getIsDeleted();

	void setIsDeleted(bool isDeleted);

	void resetAll() {
		memset(this->id, '\0', 9);
		memset(this->name, '\0', 256);
		memset(this->age, '\0', 3);
		memset(this->phone, '\0', 12);
		memset(this->cccd, '\0', 13);
		this->isDeleted = true;
	}
};

#endif
#ifndef STUDENT_H
#define STUDENT_H
#include "Utils.h"
#include<iostream>
#include <string>
using namespace std;

class Student {
private:
	char id[9];
	char name[256];
	char age[3];
	char phone[12];
	char cccd[13];
	/*char createAt[8];
	char timeAt[6];
	char dateDelete[8];
	char timeDelete[6];*/
	bool isDeleted;
public:
	void InputStudent();
	
	char* getId();
	char* getName();
	char* getAge();
	char* getPhone();
	char* getCCCD();
	bool getIsDeleted();

	void setIsDeleted(bool isDeleted);
};

#endif 
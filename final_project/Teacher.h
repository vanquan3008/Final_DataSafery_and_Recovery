#ifndef TEACHER_H
#define TEACHER_H
#include<iostream>

using namespace std;

class Teacher
{
private:	
	char id[9];
	char name[256];
	char age[3];
	char phone[12];
	char cccd[13];
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
};

#endif
#pragma once
#include<iostream>
#include <string>
#include "Main.h"
using namespace std;

class Student{
private:
	//Vị trí bắt đầu của 
	uint16_t sign;	
	bool isDelete;
	uint16_t dateDelete;
	uint16_t timedelete;
	uint32_t id;
	uint16_t userlength;
	string username;
	uint16_t age;
	uint16_t CreateAt;
	uint16_t timeAt;
	uint32_t phone;
	uint32_t CCCD;
public:
	void InputStudent();
};


#include "Teacher.h"

void Teacher::InputTeacher() {
	cout << "Nhập id:" << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.getline(this->id, sizeof(this->id));

	cout << "Nhập tên:" << endl;
	cin.getline(this->name, sizeof(this->name));

	cout << "Nhập tuổi:" << endl;
	cin.getline(this->age, sizeof(this->age));

	cout << "Nhập số điện thoại:" << endl;
	cin.getline(this->phone, sizeof(this->phone));

	cout << "Nhập cccd:" << endl;
	cin.getline(this->cccd, sizeof(this->cccd));

	this->isDeleted = false;
}

char* Teacher::getId() {
	return this->id;
}
char* Teacher::getName() {
	return this->name;
}

char* Teacher::getAge() {
	return this->age;
}

char* Teacher::getPhone() {
	return this->phone;
}

char* Teacher::getCCCD() {
	return this->cccd;
}

bool Teacher::getIsDeleted() {
	return this->isDeleted;
}

void Teacher::setIsDeleted(bool isDeleted) {
	this->isDeleted = isDeleted;
}
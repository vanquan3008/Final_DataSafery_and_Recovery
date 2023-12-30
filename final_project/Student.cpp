#include "Student.h"

void Student::InputStudent() {
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

char* Student::getId() {
	return this->id;
}
char* Student::getName() {
	return this->name;
}

char* Student::getAge() {
	return this->age;
}

char* Student::getPhone() {
	return this->phone;
}

char* Student::getCCCD() {
	return this->cccd;
}

bool Student::getIsDeleted() {
	return this->isDeleted;
}

void Student::setIsDeleted(bool isDeleted) {
	this->isDeleted = isDeleted;
}
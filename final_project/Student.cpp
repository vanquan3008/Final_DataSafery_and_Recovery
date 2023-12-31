#include "Student.h"

void Student::InputStudent() {
	string phone = "";
	string cccd = "";
	Crypto crypto;

	cout << "Input ID:" << endl;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cin.getline(this->id, sizeof(this->id));
	
	cout << "Input Name:" << endl;
	cin.getline(this->name, sizeof(this->name));

	cout << "Input Age:" << endl;
	cin.getline(this->age, sizeof(this->age));

	cout << "Input Phone Number:" << endl;
	cin >> phone;
	//cin.getline(this->phone, sizeof(this->phone));
	string hashPhone = crypto.aesEncrypt(phone);
	strcpy(this->phone, hashPhone.c_str());

	cout << "Inpute Citizen Identity Card:" << endl;
	cin >> cccd;
	//cin.getline(this->cccd, sizeof(this->cccd));
	string hashCCCD = crypto.aesEncrypt(cccd);
	strcpy(this->cccd, hashCCCD.c_str());
	
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
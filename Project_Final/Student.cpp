#include "Student.h"


void Student::InputStudent() {
	this->sign = 0;
	this->isDelete = false;
	this->dateDelete = 0;
	this->timedelete = 0;
	cout << "Enter id : ";
	cin >> this->id;
	cout << "Username : ";
	cin >> this->username;
	this->userlength = this->username.length();
	this->CreateAt = formatDateNow();
	this->timeAt = formatTimeNow();
	cout << "Age : ";
	cin >> this->age;

	//Hash Phone  and CCCD
	SHA256 sha;
	string phone, CCCD;
	cout << "Phone : ";
	cin >> phone;
	sha.update(phone);
	std::array<uint8_t, 32> digest = sha.digest();
	string phoneHash = SHA256::toString(digest);
	/*this->phone = phoneHash;

	cout << "CCCD : ";
	cin >> CCCD;
	sha.update(CCCD);
	std::array<uint8_t, 32> digest = sha.digest();
	string CCCD = SHA256::toString(digest);*/
}
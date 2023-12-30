#define _CRT_SECURE_NO_WARNINGS
#ifndef UTILS_H
#define UTILS_H
#include "SHA256.h"
#include "iostream"
#include <time.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <bitset>
#include <string>

using namespace std;

string HashPassFuc(string pass);
bool checkPassword(string pass, string passcheck);

uint16_t formatDateNow();
uint16_t formatTimeNow();
void decodeDate(uint16_t encodedDate);
void decodeTime(uint16_t encodedTime);

#endif
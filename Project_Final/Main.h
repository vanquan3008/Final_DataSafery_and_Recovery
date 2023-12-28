#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef HEADER_H
#define HEADER_H
#include <time.h>
#include <fstream>
#include "VolumeSys.h"
#include <chrono>
#include <ctime>
#include <bitset>

class VolumeSys;

using namespace std;

string HashPassFuc(string pass);
bool checkPassword(string pass, string passcheck);
bool createVolume(const string& volumeName, uint64_t volumeSize);
void formatVolume(const string& volumeName, VolumeSys& vls);

uint16_t formatDateNow();
uint16_t formatTimeNow();
void decodeDate(uint16_t encodedDate);
void decodeTime(uint16_t encodedTime);

#endif
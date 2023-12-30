#ifndef HEADER_H
#define HEADER_H
#include "VolumeSys.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <bitset>
#include <thread>

using namespace std;

bool createVolume(const string& volumeName, uint64_t volumeSize);
void formatVolume(const string& volumeName, VolumeSys& vls);
bool OpenVolume(const string& volumeName, uint64_t VolumeSize);
void changePass(string& filename);
void resetPass(string& filename);

#endif
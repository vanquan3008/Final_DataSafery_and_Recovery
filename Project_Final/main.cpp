﻿#include "Main.h"


string HashPassFuc(string pass) {
    srand(time(NULL));
    SHA256 sha;
    sha.update(pass);
    std::array<uint8_t, 32> digest = sha.digest();
    string passhash = SHA256::toString(digest);

    int size_rubbish;
    size_rubbish = rand() % 62;
    string characters = "rstuzabcEFGHIvwxyJKLlmnoMNTUVWO123ghijkP456defQRSXYZ0pqABCD789";

    string subString = characters.substr(0, size_rubbish);
    string hash = to_string(size_rubbish + 11) + subString + passhash;
    return hash;

}

bool checkPassword(string pass , string passcheck) {
    SHA256 sha;
    sha.update(pass);
    std::array<uint8_t, 32> digest = sha.digest();
    string passhash = SHA256::toString(digest);


    string rubbish = passcheck.substr(0, 2);
    int location = stoi(rubbish) - 11;
    string passlocal = passcheck.substr(2 + location, passcheck.length());
    if (passhash.compare(passlocal) == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool createVolume(const string& volumeName, uint64_t volumeSize){
    //// Kiểm tra volume tồn tại chưa
    ifstream checkFile(volumeName);
    if (checkFile.is_open())
    {
        checkFile.close();
        cout << "Volume '" << volumeName << "' đã tồn tại." << endl;
        return false;
    }
    //// Tạo volume rỗng với elements value 0
    ofstream volumeFile(volumeName, ios::out | ios::binary);
    if (volumeFile.is_open())
    { 
        // Initialize with 0
        volumeFile.seekp(0, ios::beg);
        char emptyByte = 0;
        for (uint64_t i = 0; i < volumeSize; ++i)
        {
            volumeFile.write(&emptyByte, sizeof(char));
        }
        cout << "Volume " << volumeName << " được tạo thành công." << endl;

        volumeFile.close();
        return true;
    }
    else
    {
        cout << "Không thể tạo volume." << endl;
        return false;
    }
}


void formatVolume(const string& volumeName, VolumeSys& vls) {
    fstream volumeFile(volumeName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        string checkfile;
        string password;

        while (true) {
            cout << "Do you want to set Password to file(Yes/No) : ";
            cin >> checkfile;
            if (checkfile == "Yes" || checkfile == "No") {
                break;
            }
            else {
                cout << "The request to select Yes or No must not select another request" << endl;
            }

        }
        if (checkfile == "Yes") {
            cout << "Password : ";
            cin >> password;
        }
        vls.setPassword(password);

        volumeFile.seekp(0, ios::beg);
        vls.WriteVolume(volumeFile);
        cout << "Volume '" << volumeName << "' được định dạng thành công." << endl;
        volumeFile.close();
    }
    else
    {
        cout << "Không thể mở volume/ volume không tồn tại." << endl;
    }
}

uint16_t formatDateNow() {
    auto now = std::chrono::system_clock::now();
    // Chuyển đổi sang kiểu time_t
    time_t now_c = std::chrono::system_clock::to_time_t(now);
    // Chuyển đổi sang kiểu tm (struct chứa thông tin ngày tháng năm)
    tm* now_tm = std::localtime(&now_c);
    // Lấy ngày tháng năm từ struct tm
    int year = now_tm->tm_year + 1900; // Năm tính từ 1900
    int month = now_tm->tm_mon + 1;    // Tháng tính từ 0 (0 - 11)
    int day = now_tm->tm_mday;         // Ngày trong tháng (1 - 31)

    if (year < 1970 || year > 2127 || month < 1 || month > 12 || day < 1 || day > 31) {
        cout << "Do not format day from uint_16" << endl;
        return 0; // Ví dụ: Trả về 0 để biểu thị lỗi
    }
    // Mã hóa thông tin ngày tháng năm thành 16 bit
    uint16_t encodedDate = ((year - 1970) << 9) | (month << 5) | day;

    return encodedDate;
}



void decodeDate(uint16_t encodedDate) {
    uint16_t year = (encodedDate >> 9) + 1970;
    uint16_t month = (encodedDate >> 5) & 0xF;
    uint16_t day = encodedDate & 0x1F;

    std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;
}


uint16_t formatTimeNow(){
    uint16_t timeData = 0;
    auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    // Chuyển đổi thời gian thành struct tm để lấy ngày tháng năm, giờ, phút và giây
    std::tm* timeInfo = std::localtime(&currentTime);

    // Lấy thông tin giờ, phút và giây
    int hour = timeInfo->tm_hour;    // Giờ
    int minute = timeInfo->tm_min;   // Phút
    int second = timeInfo->tm_sec;   // Giây


    timeData |= (hour << 11);    // Sử dụng 5 bit (từ bit 11 đến bit 15) để lưu giữ giờ
    timeData |= (minute << 5);   // Sử dụng 6 bit (từ bit 5 đến bit 10) để lưu giữ phút
    timeData |= second;          // Sử dụng 5 bit (từ bit 0 đến bit 4) để lưu giữ giây



    uint16_t encodedTime = (hour << 11) | (minute << 5) | second/2;
    // In ra dãy bit biểu diễn thông tin thời gian

    return encodedTime;

}

void decodeTime(uint16_t encodedTime) {
    uint16_t hour = (encodedTime >> 11);
    uint16_t minute = (encodedTime >> 5) & 0xF;
    uint16_t second = encodedTime & 0x1F;

    std::cout << "hour: " << hour << ", minute: " << minute << ", second: " << second << std::endl;
}
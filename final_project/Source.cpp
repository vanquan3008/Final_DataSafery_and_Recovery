#include "Header.h"

bool createVolume(const string& volumeName, uint64_t volumeSize) {
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
    //fstream volumeFile(volumeName, ios::in | ios::out | ios::binary);
    ofstream volumeFile(volumeName, ios::out | ios::binary);

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

        
        cout << "File '" << volumeName << "' được định dạng thành công." << endl;
        volumeFile.close();
    }
    else
    {
        cout << "Không thể mở volume/ volume không tồn tại." << endl;
    }
}

bool OpenVolume(const string& volumeName, uint64_t VolumeSize) {
    fstream f(volumeName);
    VolumeSys vls = VolumeSys(VolumeSize);
    //Đọc dữ liệu đầu vào lưu vào vls 

    vls.ReadVolume(volumeName);

    int maxAttempts = 5; // Số lần nhập sai tối đa
    int currentAttempts = 0; // Số lần nhập sai hiện tại
    int waitTime = 5; // Thời gian đợi ban đầu sau lần nhập sai đầu (5 giây)
    if (vls.getPass() == "") {
        return true;
    }
    while (currentAttempts < maxAttempts) {
        string inputPassword;
        cout << "Input Password: ";
        cin >> inputPassword;

        if (checkPassword(inputPassword, vls.getPass())) {
            std::cout << "Open file sucessfully!\n";
            return true;
        }
        else {
            currentAttempts++;
            if (currentAttempts < maxAttempts) {
                std::cout << "Pass error.Please re-enter your password. \n";
                for (int i = waitTime; i > 0; i--) {
                    cout << "Waiting " << i << " seconds...\n";
                    this_thread::sleep_for(std::chrono::seconds(1));
                }
                waitTime *= 2; // Tăng thời gian đợi sau mỗi lần nhập sai lên gấp đôi
                cout << "Number of remaining attempts : " << maxAttempts - currentAttempts - 1 << endl;

            }
            else {
                std::cout << "The number of incorrect entries is too many. Try again later.\n";
                return false;
            }
        }

    }
}


void changePass(string& filename) {
    
    VolumeSys vls ;
    string oldPass;
    cout << "Input old pass : ";
    cin >> oldPass;
    vls.ReadVolume(filename);

    cout << vls.getPass() << endl;
    string newpass;
    if (checkPassword(oldPass, vls.getPass())) {
        //Check pass cu
        cout << "Input new Pass can change : ";
        cin >> newpass;
        ofstream f(filename);
        vls.setPassword(newpass);
        f.seekp(0, ios::beg);
        vls.WriteVolume(f);
        cout << "Change password sucessfully." << endl;
    }
    else {
        cout << "Your old password is incorrect ." << endl;
    }
}


void resetPass(string& filename) {
    srand(time(NULL));
    int numbergacha;
    int numbercheck;
    while (true) {
        numbergacha = rand() % 9000 + 1000;
        cout << "Input number see this PC " << endl;
        cout << "Number : " << numbergacha << endl;
        cout << "Input number(Input 0 to exits resetpass) : ";
        cin >> numbercheck;
        if (numbercheck == numbergacha) {
            cout << "Verify success fully";
            break;
        }
        if (numbercheck == 0) {
            cout << "Exit!";
            return;
        }

    }

    VolumeSys vls;
    ofstream f(filename);
    vls.ReadVolume(filename);
    // Set pass "0000"
    cout << "Password reset to 0000 ." << endl;
    vls.setPassword("0000");

    // Read volume sys
    f.seekp(0, ios::beg);
    vls.WriteVolume(f);
    cout << "Password reset sucessfully ." << endl;
}
#include "VolumeSys.h"

VolumeSys::VolumeSys() {
    this->volumeSize = 0;

    this->ArrTeacherSize = 0;
    this->ArrStudentSize = 0;

    memset(this->password, '\0', 65);
}

VolumeSys::VolumeSys(uint64_t volumeSize) {
    this->volumeSize = volumeSize;

    this->ArrTeacherSize = 0;
    this->ArrStudentSize = 0;

    memset(this->password, '\0', 65);
}

void VolumeSys::setPassword(string pass) {
    string hash = HashPassFuc(pass);
    strcpy(this->password, hash.c_str());
}

void VolumeSys::ReadVolume(string fileName)
{
    ifstream inFile(fileName, ios::in | ios::binary);

    if (inFile.is_open()) {
        inFile.read((char*)&this->volumeSize, sizeof(this->volumeSize));
        inFile.read((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
        inFile.read((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
        inFile.read((char*)&this->password, sizeof(this->password));
        
        inFile.close();
    }
    else {
        cout << "Unable to open the file for reading." << endl;
    }
    
}

void VolumeSys::WriteVolume(ofstream& file)
{
    // Ghi header
    file.write((char*)&this->volumeSize, sizeof(this->volumeSize));
    file.write((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
    file.write((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
    file.write((char*)&this->password, sizeof(this->password));

    // Ghi Backup
    file.write((char*)&this->volumeSize, sizeof(this->volumeSize));
    file.write((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
    file.write((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
    file.write((char*)&this->password, sizeof(this->password));


    // Khởi tạo một khoảng byte rỗng giá trị 0
    // Vùng này dùng để chứa thông tin giáo viên khi thêm mới
    // Vùng lưu trữ chiếm 10% tổng kích thước volume
    size_t teacherDataSize = static_cast<size_t>(this->volumeSize * 0.1);
    char* emptyBuffer = new char[teacherDataSize];
    std::fill(emptyBuffer, emptyBuffer + teacherDataSize, 0);
    file.write(emptyBuffer, teacherDataSize);
}

void VolumeSys::AddStudent(Student& student, string fileName) {
    // Mở file append thông tin sinh viên
    ofstream volumeFile(fileName, ios::out | ios::binary | ios::app);

    if (volumeFile.is_open()) {
        // Di chuyển đến cuối file
        volumeFile.seekp(0, ios::end);

        // Ghi thông tin sinh viên
        volumeFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));

        cout << "Add new student successfully." << endl;
        volumeFile.close();
    }
    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }

    
}

void VolumeSys::ReadStudentList(string fileName) {
    vector<Student> students;

    // Mở file đọc thông tin sinh viên
    ifstream volumeFile(fileName, ios::in | ios::binary);

    if (volumeFile.is_open()) {
        // Lấy kích thước chứa vùng dữ liệu giáo viên
        size_t teacherDataSize = static_cast<size_t>(this->volumeSize * 0.1);

        // Skip header
        // Vùng lưu trữ thông tin sinh viên bắt đầu sau vùng dự trữ thông tin giáo viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2 + 
            sizeof(this->password))*2 + teacherDataSize, ios::beg);

        // Đọc thông tin sinh viên
        while (!volumeFile.eof()) {
            Student student;
            volumeFile.read(reinterpret_cast<char*>(&student), sizeof(Student));

            // Nếu đọc thành công thì thêm vào vector
            if (volumeFile.gcount() == sizeof(Student)) {
                if (!student.getIsDeleted()) {
                    students.push_back(student);
                }
            }
        }

        // In thông tin sinh viên
        Crypto crypto;

        cout << "=== STUDENT LIST ===" << endl;
        for (auto& student : students) {
            cout << "ID: " << student.getId() << endl;
            cout << "Name: " << student.getName() << endl;
            cout << "Age: " << student.getAge() << endl;
            cout << "Phone number: " << crypto.aesDecrypt(student.getPhone()) << endl;
            cout << "Citizen Identity Card: " << crypto.aesDecrypt(student.getCCCD()) << endl;
            cout << endl;
        }
        cout << "====================" << endl;

        volumeFile.close();
    }

    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }
  
}

void VolumeSys::DeleteOrRestoreStudent(string fileName, const char* studentId, bool isDeleted) {
    bool isExisted = false;
    
    // Mở file ghi đè thông tin có sẵn
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Lấy kích thước chứa vùng dữ liệu giáo viên
        size_t teacherDataSize = static_cast<size_t>(this->volumeSize * 0.1);

        // Di chuyển tới offset bắt đầu của vùng lưu trữ dữ liệu sinh viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2 +
            sizeof(this->password))*2
            + teacherDataSize, ios::beg);

        // Tìm sinh viên bằng id
        while (!volumeFile.eof()) {
            Student student;
            streampos currentPos = volumeFile.tellg();
            volumeFile.read(reinterpret_cast<char*>(&student), sizeof(Student));

            // Xóa sinh viên
            if (strcmp(student.getId(), studentId) == 0 && isDeleted) {
                if (!student.getIsDeleted())
                {
                    // Đánh dấu sinh viên đã bị xóa
                    // Chuyển isDeleted thành true
                    student.setIsDeleted(true);
                    volumeFile.seekp(currentPos);
                    volumeFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
                    cout << "Delete student successfully." << endl;
                    isExisted = true;
                    break;
                }
            }

            // Phục hồi sinh viên
            else if (strcmp(student.getId(), studentId) == 0 && !isDeleted) {
                if (student.getIsDeleted())
                {
                    // Đánh dấu sinh viên được phục hồi 
                    // Chuyển isDeleted thành false
                    student.setIsDeleted(false);
                    volumeFile.seekp(currentPos);
                    volumeFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
                    cout << "Restore student successfully." << endl;
                    isExisted = true;
                    break;
                }
            }
        }

        if (!isExisted)
        {
            cout << "This student isn't in delete list." << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }
}

void VolumeSys::AddTeacher(Teacher& teacher, string fileName) {
    // Mở file và ghi đè dữ liệu đã có
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Tính offset dựa trên số phần tử giáo viên
        streampos position = (sizeof(uint64_t) + sizeof(uint16_t) * 2 + 
            sizeof(this->password)) * 2
            + sizeof(Teacher) * this->ArrTeacherSize;

        // Di chuyển đến offset
        volumeFile.seekp(position, std::ios::beg);

        // Ghi đè dữ liệu giáo viên mới vào dữ liệu rỗng
        volumeFile.write(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));

        cout << "Add new teacher successfully." << endl;

        // Close the file
        volumeFile.close();
    }
    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }
}

void VolumeSys::UpdateTeacherSize(string fileName) {
    // Cập nhật số phần tử giáo viên
    this->ArrTeacherSize++;

    // Mở file và ghi đè dữ liệu đã có
    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

    if (file.is_open()) {
        // Tính offset nơi lưu trữ số phần tử giáo viên
        std::streampos offset = sizeof(uint64_t) + sizeof(uint16_t);

        // Di chuyển đến offset đó
        file.seekp(offset, std::ios::beg);

        // Thực hiện ghi đè số phần tử giáo viên mới
        file.write(reinterpret_cast<char*>(&this->ArrTeacherSize), sizeof(this->ArrTeacherSize));

        // Update trên backup
        offset = sizeof(uint64_t) + sizeof(uint16_t) * 2 +
            sizeof(this->password)
            + sizeof(uint64_t) + sizeof(uint16_t);
        file.seekp(offset, std::ios::beg);
        file.write(reinterpret_cast<char*>(&this->ArrTeacherSize), sizeof(this->ArrTeacherSize));

        file.close();
    }
}

void VolumeSys::ReadTeacherList(string fileName) {
    vector<Teacher> teachers;

    // Mở file
    ifstream volumeFile(fileName, ios::in | ios::binary);

    if (volumeFile.is_open()) {
        // Tính offset kết thúc dữ liệu hiện có của giáo viên
        // Offset được tính dựa trên số phần tử giáo viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2
            + sizeof(this->password))*2
            + sizeof(Teacher) * this->ArrTeacherSize, ios::beg);
        streampos endPos = volumeFile.tellg();

        // Skip header
        // Vùng thông tin giáo viên nằm sau backup
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2
            + sizeof(this->password))*2, ios::beg);
        streampos currentPos = volumeFile.tellg();

        // Đọc thông tin từng giáo viên
        while (currentPos < endPos) {
            
            Teacher teacher;
            volumeFile.read(reinterpret_cast<char*>(&teacher), sizeof(Teacher));

            // Nếu đọc thành công thì thêm vào vector
            if (volumeFile.gcount() == sizeof(Teacher)) {
                if (!teacher.getIsDeleted()) {
                    teachers.push_back(teacher);
                }
            }

            // Cập nhật lại offset hiện tại
            currentPos = volumeFile.tellg();
        }

        Crypto crypto;

        // In thông tin giáo viên
        if (this->ArrTeacherSize > 0)
        {
            cout << "=== TEACHER LIST ===" << endl;
            for (auto& teacher : teachers) {
                cout << "ID: " << teacher.getId() << endl;
                cout << "Name: " << teacher.getName() << endl;
                cout << "Age: " << teacher.getAge() << endl;
                cout << "Phone number: " << crypto.aesDecrypt(teacher.getPhone()) << endl;
                cout << "Citizen Identity Card: " << crypto.aesDecrypt(teacher.getCCCD()) << endl;
                cout << endl;
                
            }
            cout << "====================" << endl;
        }

        else
        {
            cout << "=== TEACHER LIST ===" << endl;
            cout << "====================" << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }

}

void VolumeSys::DeleteOrRestoreTeacher(string fileName, const char* teacherId, bool isDeleted) {
    bool isExisted = false;
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Tính offset kết thúc dữ liệu hiện có của giáo viên
        // Offset được tính dựa trên số phần tử giáo viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2
            + sizeof(this->password))*2
            + sizeof(Teacher) * this->ArrTeacherSize, ios::beg);
        streampos endPos = volumeFile.tellg();

        // Di chuyển đến offset bắt đầu vùng thông tin giáo viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2
            + sizeof(this->password))*2, ios::beg);
        streampos currentPos = volumeFile.tellg();

        // Đọc thông tin từng giáo viên
        while (currentPos < endPos) {
            Teacher teacher;
            volumeFile.read(reinterpret_cast<char*>(&teacher), sizeof(Teacher));

            // Xóa giáo viên
            if (strcmp(teacher.getId(), teacherId) == 0 && isDeleted) {
                if (!teacher.getIsDeleted())
                {
                    // Đánh dấu giáo viên bị xóa
                    // Chuyển isDeleted thành true
                    teacher.setIsDeleted(true);
                    volumeFile.seekp(currentPos);
                    volumeFile.write(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));
                    cout << "Delete teacher successfully." << endl;
                    isExisted = true;
                    break;
                }
            }

            // Phục hồi giáo viên
            else if (strcmp(teacher.getId(), teacherId) == 0 && !isDeleted) {
                if (teacher.getIsDeleted())
                {
                    // Đánh dấu giáo viên được phục hồi
                    // Chuyển isDeleted thành false
                    teacher.setIsDeleted(false);
                    volumeFile.seekp(currentPos);
                    volumeFile.write(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));
                    cout << "Restore teacher successfully." << endl;
                    isExisted = true;
                    break;
                }
            }

            // Cập nhật lại offset hiện tại
            currentPos = volumeFile.tellg();
        }

        if (!isExisted)
        {
            cout << "This teacher isn't in delete list." << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }
}

void VolumeSys::UpdatePassword(string fileName) {
    // Mở file và ghi đè dữ liệu đã có
    std::fstream file(fileName, std::ios::in | std::ios::out | std::ios::binary);

    if (file.is_open()) {
        // Tính offset nơi lưu trữ số phần tử giáo viên
        std::streampos offset = sizeof(uint64_t) + sizeof(uint16_t) * 2;

        // Di chuyển đến offset đó
        file.seekp(offset, std::ios::beg);

        // Thực hiện ghi đè password
        file.write(reinterpret_cast<char*>(&this->password), sizeof(this->password));

        // Update backup password
        offset = sizeof(uint64_t) + sizeof(uint16_t) * 2 +
            sizeof(this->password) + sizeof(uint64_t) + sizeof(uint16_t) * 2;
        file.seekp(offset, std::ios::beg);
        file.write(reinterpret_cast<char*>(&this->password), sizeof(this->password));
        file.close();
    }
}

void VolumeSys::DeleteStudentPermanently(string fileName, const char* studentId) {
    bool isExisted = false;

    // Mở file ghi đè thông tin có sẵn
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Lấy kích thước chứa vùng dữ liệu giáo viên
        size_t teacherDataSize = static_cast<size_t>(this->volumeSize * 0.1);

        // Di chuyển tới offset bắt đầu của vùng lưu trữ dữ liệu sinh viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2 +
            sizeof(this->password)) * 2 + teacherDataSize, ios::beg);

        // Tìm sinh viên bằng id
        while (!volumeFile.eof()) {
            Student student;
            streampos currentPos = volumeFile.tellg();
            volumeFile.read(reinterpret_cast<char*>(&student), sizeof(Student));

            // Xóa sinh viên
            if (strcmp(student.getId(), studentId) == 0) {
                // Overwrite các byte dữ liệu sinh viên hiện tại thành byte rỗng
                student.resetAll();
                volumeFile.seekp(currentPos);
                volumeFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
                cout << "Delete student successfully." << endl;
                isExisted = true;
                break;
            }
        }

        if (!isExisted)
        {
            cout << "This student isn't existed." << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }
}

void VolumeSys::DeleteTeacherPermanently(string fileName, const char* teacherId) {
    bool isExisted = false;
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Tính offset kết thúc dữ liệu hiện có của giáo viên
        // Offset được tính dựa trên số phần tử giáo viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2
            + sizeof(this->password))*2 + sizeof(Teacher) * this->ArrTeacherSize, ios::beg);
        streampos endPos = volumeFile.tellg();

        // Di chuyển đến offset bắt đầu vùng thông tin giáo viên
        volumeFile.seekg((sizeof(uint64_t) + sizeof(uint16_t) * 2
            + sizeof(this->password))*2, ios::beg);
        streampos currentPos = volumeFile.tellg();

        // Đọc thông tin từng giáo viên
        while (currentPos < endPos) {
            Teacher teacher;
            volumeFile.read(reinterpret_cast<char*>(&teacher), sizeof(Teacher));

            // Xóa giáo viên
            if (strcmp(teacher.getId(), teacherId) == 0) {
                // Overwrite các byte dữ liệu sinh viên hiện tại thành byte rỗng
                teacher.resetAll();
                volumeFile.seekp(currentPos);
                volumeFile.write(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));
                cout << "Delete teacher successfully." << endl;
                isExisted = true;
                break;
            }

            // Cập nhật lại offset hiện tại
            currentPos = volumeFile.tellg();
        }

        if (!isExisted)
        {
            cout << "This teacher isn't existed" << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Cannot open file or this file is not existed." << endl;
    }
}
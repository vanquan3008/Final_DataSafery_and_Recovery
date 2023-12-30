#include "VolumeSys.h"





VolumeSys::VolumeSys() {
    this->volumeSize = 0;

    this->ArrTeacherSize = 0;
    this->ArrStudentSize = 0;

    this->passsize = 127;
    this->password = "";
}
VolumeSys::VolumeSys(uint64_t volumeSize) {
    this->volumeSize = volumeSize;

    this->ArrTeacherSize = 0;
    this->ArrStudentSize = 0;

    this->passsize = 127;
    this->password = "";
}

void VolumeSys::setPassword(string pass) {
    this->password = HashPassFuc(pass);
    this->passsize = static_cast<uint16_t>(127);
}

void VolumeSys::ReadVolume(string fileName)
{
    ifstream inFile(fileName, ios::in | ios::binary);

    if (inFile.is_open()) {
        inFile.read((char*)&this->volumeSize, sizeof(this->volumeSize));
        inFile.read((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
        inFile.read((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
        inFile.read((char*)&this->passsize, sizeof(this->passsize));
        this->password.resize(this->passsize);
        inFile.read((char*)this->password.c_str(), this->passsize);

        inFile.close();
    }
    else {
        cout << "Unable to open the file for reading." << endl;
    }
    
}

void VolumeSys::WriteVolume(ofstream& file)
{
    file.write((char*)&this->volumeSize, sizeof(this->volumeSize));
    file.write((char*)&this->ArrStudentSize, sizeof(this->ArrStudentSize));
    file.write((char*)&this->ArrTeacherSize, sizeof(this->ArrTeacherSize));
    file.write((char*)&this->passsize, sizeof(this->passsize));
    this->password.resize(this->passsize);
    file.write((char*)this->password.c_str(), this->passsize);

    // Khởi tạo một khoảng byte rỗng giá trị 0
    // Vùng này dùng để chứa thông tin giáo viên khi thêm mới
    // Mặc định vùng dự trữ có thể chứa được 100 giáo viên
    //size_t sizeInBytes = sizeof(Teacher) * 100;
    //char* emptyBuffer = new char[sizeof(Teacher) * 100];
    //std::fill(emptyBuffer, emptyBuffer + sizeInBytes, 0);
    //file.write(emptyBuffer, sizeInBytes);
}

void VolumeSys::AddStudent(Student& student, string fileName) {
    // Mở file append thông tin sinh viên
    ofstream volumeFile(fileName, ios::out | ios::binary | ios::app);

    if (volumeFile.is_open()) {
        // Di chuyển đến cuối file
        volumeFile.seekp(0, ios::end);

        // Ghi thông tin sinh viên
        volumeFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));

        cout << "Thêm sinh viên thành công." << endl;
        volumeFile.close();
    }
    else {
        cout << "Không thể mở file / File không tồn tại." << endl;
    }

    
}

void VolumeSys::ReadStudentList(string fileName) {
    vector<Student> students;

    // Mở file đọc thông tin sinh viên
    ifstream volumeFile(fileName, ios::in | ios::binary);

    if (volumeFile.is_open()) {
        // Skip header
        // Vùng lưu trữ thông tin sinh viên bắt đầu sau vùng dự trữ thông tin giáo viên
        volumeFile.seekg(sizeof(uint64_t) + sizeof(uint16_t) * 3 + 
            this->passsize + sizeof(Teacher) * 100, ios::beg);

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
        cout << "=== Danh sách sinh viên ===" << endl;
        for (auto& student : students) {
            cout << "Mã số sinh viên: " << student.getId() << endl;
            cout << "Tên: " << student.getName() << endl;
            cout << "Tuổi: " << student.getAge() << endl;
            cout << "Số điện thoại: " << student.getPhone() << endl;
            cout << "Căn cước công dân: " << student.getCCCD() << endl;
            cout << endl;
        }
        cout << "====================" << endl;

        volumeFile.close();
    }

    else {
        cout << "Không thể mở file / File không tồn tại." << endl;
    }
  
}

void VolumeSys::DeleteOrRestoreStudent(string fileName, const char* studentId, bool isDeleted) {
    bool isExisted = false;
    
    // Mở file ghi đè thông tin có sẵn
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Di chuyển tới offset bắt đầu của vùng lưu trữ dữ liệu sinh viên
        volumeFile.seekg(sizeof(uint64_t) + sizeof(uint16_t) * 3 +
            this->passsize + sizeof(Teacher) * 100, ios::beg);

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
                    cout << "Xóa sinh viên thành công." << endl;
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
                    cout << "Phục hồi sinh viên thành công." << endl;
                    isExisted = true;
                    break;
                }
            }
        }

        if (!isExisted)
        {
            cout << "Sinh viên này không tồn tại trong mục xóa." << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Không thể mở file / File không tồn tại." << endl;
    }
}

void VolumeSys::AddTeacher(Teacher& teacher, string fileName) {
    // Mở file và ghi đè dữ liệu đã có
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Tính offset dựa trên số phần tử giáo viên
        streampos position = sizeof(uint64_t) + sizeof(uint16_t) * 3 + this->passsize
            + sizeof(Teacher) * this->ArrTeacherSize;

        // Di chuyển đến offset
        volumeFile.seekp(position, std::ios::beg);

        // Ghi đè dữ liệu giáo viên mới vào dữ liệu rỗng
        volumeFile.write(reinterpret_cast<const char*>(&teacher), sizeof(Teacher));

        cout << "Thêm giáo viên thành công." << endl;

        // Close the file
        volumeFile.close();
    }
    else {
        cout << "Không thể mở file / File không tồn tại." << endl;
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
        volumeFile.seekg(sizeof(uint64_t) + sizeof(uint16_t) * 3
            + this->passsize + sizeof(Teacher) * this->ArrTeacherSize, ios::beg);
        streampos endPos = volumeFile.tellg();

        // Skip header
        // Vùng thông tin giáo viên nằm sau header
        volumeFile.seekg(sizeof(uint64_t) + sizeof(uint16_t) * 3
            + this->passsize, ios::beg);
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

        // In thông tin giáo viên
        if (this->ArrTeacherSize > 0)
        {
            cout << "=== Danh sách giáo viên ===" << endl;
            for (auto& teacher : teachers) {
                cout << "Mã số giáo viên: " << teacher.getId() << endl;
                cout << "Tên: " << teacher.getName() << endl;
                cout << "Tuổi: " << teacher.getAge() << endl;
                cout << "Số điện thoại: " << teacher.getPhone() << endl;
                cout << "Căn cước công dân: " << teacher.getCCCD() << endl;
                cout << endl;
                
            }
            cout << "====================" << endl;
        }

        else
        {
            cout << "=== Danh sách giáo viên ===" << endl;
            cout << "====================" << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Không thể mở file / File không tồn tại." << endl;
    }

}

void VolumeSys::DeleteOrRestoreTeacher(string fileName, const char* teacherId, bool isDeleted) {
    bool isExisted = false;
    fstream volumeFile(fileName, ios::in | ios::out | ios::binary);

    if (volumeFile.is_open()) {
        // Tính offset kết thúc dữ liệu hiện có của giáo viên
        // Offset được tính dựa trên số phần tử giáo viên
        volumeFile.seekg(sizeof(uint64_t) + sizeof(uint16_t) * 3
            + this->passsize + sizeof(Teacher) * this->ArrTeacherSize, ios::beg);
        streampos endPos = volumeFile.tellg();

        // Di chuyển đến offset bắt đầu vùng thông tin giáo viên
        volumeFile.seekg(sizeof(uint64_t) + sizeof(uint16_t) * 3
            + this->passsize, ios::beg);
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
                    cout << "Xóa giáo viên thành công." << endl;
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
                    cout << "Phục hồi giáo viên thành công." << endl;
                    isExisted = true;
                    break;
                }
            }

            // Cập nhật lại offset hiện tại
            currentPos = volumeFile.tellg();
        }

        if (!isExisted)
        {
            cout << "Giáo viên này không tồn tại trong mục xóa." << endl;
        }

        volumeFile.close();
    }

    else {
        cout << "Không thể mở file / File không tồn tại." << endl;
    }
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Header.h"

using namespace std;
int main()
{
    uint64_t volumeSize = 1024 * 1024;
    VolumeSys volumeSys = VolumeSys(volumeSize);

    string name = "";
    string nn = "";
    int inputSize = 0;

    char id[9];

    int choice = 0;

    cout << sizeof(Teacher) << endl;
    cout << (volumeSize * 10) / sizeof(Teacher) << endl;
    cout << round(((volumeSize * 10) / sizeof(Teacher)) * 0.1);

    do
    {
        system("pause");
        system("cls");
        cout << "\t\t\tTHIET LAP FILE" << endl;
        cout << "\t\t1. Tạo và định dạng file chứa danh sách." << endl;
        cout << "\t\t2. Thêm sinh viên." << endl;
        cout << "\t\t3. Hiển thị danh sách sinh viên." << endl;
        cout << "\t\t4. Xóa sinh viên." << endl;
        cout << "\t\t5. Phục hồi sinh viên đã xóa." << endl;
        cout << "\t\t6. Thêm giáo viên." << endl;
        cout << "\t\t7. Hiển thị danh sách giáo viên." << endl;
        cout << "\t\t8. Xóa giáo viên." << endl;
        cout << "\t\t9. Phục hồi giáo viên đã xóa." << endl;
        cout << "\t\t10. Đổi mật khẩu file." << endl;
        cout << "\t\t11. Reset password." << endl;
        cout << "Lựa chọn: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;

            cout << "Nhập kích thước file (MB): " << endl;
            cin >> inputSize;

            if (createVolume(name, (volumeSize * inputSize)))
            {
                formatVolume(name, volumeSys);
            }
            cout << endl;
            break;

        case 2:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            Student student;
            if (OpenVolume(name, volumeSize * inputSize)) {
                student.InputStudent();
                volumeSys.ReadVolume(name);
                volumeSys.AddStudent(student, name);
            }
            cout << endl;
            break;

        case 3:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.ReadStudentList(name);
            }
            cout << endl;
            break;

        case 4: 
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            cout << "Nhập mã số sinh viên của sinh viên cần xóa:" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(id, sizeof(id));

            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreStudent(name, id, true);
            }
            break;

        case 5:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            cout << "Nhập mã số sinh viên của sinh viên cần phục hồi:" << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(id, sizeof(id));

            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreStudent(name, id, false);
            }
            break;

        case 6:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            Teacher teacher;
            volumeSys.ReadVolume(name);
            if (OpenVolume(name, volumeSize * inputSize)) {
                teacher.InputTeacher();
                volumeSys.AddTeacher(teacher, name);
                volumeSys.UpdateTeacherSize(name);
            }
            cout << endl;
            break;

        case 7:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.ReadTeacherList(name);
            }
            cout << endl;
            break;

        case 8:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                cout << "Nhập mã số của giáo viên cần xóa:" << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.getline(id, sizeof(id));

                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreTeacher(name, id, true);
            }
            break;

        case 9:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                cout << "Nhập mã số của giáo viên cần phục hồi:" << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.getline(id, sizeof(id));

                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreTeacher(name, id, false);
            }
            break;
        case 10:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            changePass(name);
            break;
        case 11:
            cout << "Nhập tên file (VD: filename.bin): " << endl;
            cin >> name;
            resetPass(name);
            break;
        default:
            break;
        }

    } while (choice != 0);

    return 0;

    //decodeTime(formatTimeNow());

    /*f.open(name, ios::in);
    vlss.ReadVolume(f);
    cout << vlss.getPasssize() << endl;
    cout << "Nhập mật khẩu cần check : " << endl;

    cin >> nn;
    cout << checkPassword(nn, vlss.getPass());*/
}
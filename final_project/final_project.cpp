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

    do
    {
        system("pause");
        system("cls");

        cout << "\t\t1. Create and format file." << endl;
        cout << "\t\t2. Add new student." << endl;
        cout << "\t\t3. Display list of students." << endl;
        cout << "\t\t4. Delete a student by id." << endl;
        cout << "\t\t5. Restore a student by id." << endl;
        cout << "\t\t6. Add new teacher." << endl;
        cout << "\t\t7. Display list of teachers." << endl;
        cout << "\t\t8. Delete a teacher by id." << endl;
        cout << "\t\t9. Restore a teacher by id." << endl;
        cout << "\t\t10. Change file's password." << endl;
        cout << "\t\t11. Reset current password." << endl;
        cout << "\t\t12. Delete a student by id permanently." << endl;
        cout << "\t\t13. Delete a teacher by id permanently." << endl;

        cout << "Lựa chọn: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;

            cout << "Input file size (Ex: input '10' for 10MB): " << endl;
            cin >> inputSize;

            if (createVolume(name, (volumeSize * inputSize)))
            {
                formatVolume(name, volumeSys);
            }
            cout << endl;
            break;

        case 2:
            cout << "Input file name (Ex: filename.bin): " << endl;
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
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.ReadStudentList(name);
            }
            cout << endl;
            break;

        case 4: 
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            cout << "Input student ID: " << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(id, sizeof(id));

            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreStudent(name, id, true);
            }
            break;

        case 5:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            cout << "Input student ID: " << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(id, sizeof(id));

            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreStudent(name, id, false);
            }
            break;

        case 6:
            cout << "Input file name (Ex: filename.bin): " << endl;
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
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.ReadTeacherList(name);
            }
            cout << endl;
            break;

        case 8:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                cout << "Input teacher ID: " << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.getline(id, sizeof(id));

                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreTeacher(name, id, true);
            }
            break;

        case 9:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            if (OpenVolume(name, volumeSize * inputSize)) {
                cout << "Input teacher ID: " << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.getline(id, sizeof(id));

                volumeSys.ReadVolume(name);
                volumeSys.DeleteOrRestoreTeacher(name, id, false);
            }
            break;
        case 10:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            changePass(name);
            break;

        case 11:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            resetPass(name);
            break;
        
        case 12:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            cout << "Input student ID: " << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(id, sizeof(id));

            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.DeleteStudentPermanently(name, id);
            }
            break;

        case 13:
            cout << "Input file name (Ex: filename.bin): " << endl;
            cin >> name;
            cout << "Input teacher ID: " << endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin.getline(id, sizeof(id));

            if (OpenVolume(name, volumeSize * inputSize)) {
                volumeSys.ReadVolume(name);
                volumeSys.DeleteTeacherPermanently(name, id);
            }
            break;
        
        default:
            break;
        }

    } while (choice != 0);

    return 0;
}
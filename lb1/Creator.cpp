#define _CRT_SECURE_NO_WARNINGS // Отключаем предупреждение о небезопасных функциях
#include <windows.h>
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Employee
{
    int ID;
    char name[10];
    double hours;
};

void createEmployeeFile(const wstring& outputFileName, int numEmployees) {
    HANDLE hFile = CreateFile(outputFileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Error opening output file." << endl;
        return;
    }

    Employee Bob = { 0 }; // Инициализация структуры нулями
    string buff;

    for (int i = 0; i < numEmployees; i++) {
        cout << "Enter info about employee: ID, name, hours" << endl;
        while (true) {
            cout << "ID: ";
            if (cin >> Bob.ID) {
                cout << "Name: ";
                cin >> buff;
                cout << "Hours: ";
                if (cin >> Bob.hours) {
                    break;
                }
            }
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            cout << "Invalid input. Please enter integer ID, string name, and floating-point hours." << endl;
        }

        // Используем strncpy_s для безопасного копирования
        strncpy_s(Bob.name, buff.c_str(), 9);
        Bob.name[9] = '\0';

        DWORD bytesWritten = 0; // Инициализация переменной
        if (!WriteFile(hFile, &Bob, sizeof(Employee), &bytesWritten, NULL)) {
            cout << "Error writing to file." << endl;
            CloseHandle(hFile);
            return;
        }
    }

    CloseHandle(hFile);
    cout << "File created successfully." << endl;
}

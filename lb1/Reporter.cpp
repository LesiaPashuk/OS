#define _CRT_SECURE_NO_WARNINGS // Отключаем предупреждение о небезопасных функциях
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Employee
{
    int num;
    char name[10];
    double hours;
};

void generateReport(const wstring& inputFileName, const wstring& outputFileName, int paymentRate) {
    HANDLE hFile = CreateFile(inputFileName.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Error opening input file." << endl;
        return;
    }

    HANDLE hOutFile = CreateFile(outputFileName.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hOutFile == INVALID_HANDLE_VALUE) {
        cout << "Error opening output file." << endl;
        CloseHandle(hFile);
        return;
    }

    vector<Employee> vecEmployees;
    Employee Bob = { 0 }; // Инициализация структуры нулями
    DWORD bytesRead = 0; // Инициализация переменной

    while (ReadFile(hFile, &Bob, sizeof(Employee), &bytesRead, NULL) && bytesRead > 0) {
        vecEmployees.push_back(Bob);
    }

    sort(vecEmployees.begin(), vecEmployees.end(), [](const Employee& a, const Employee& b) {
        return a.num < b.num;
        });

    for (const auto& emp : vecEmployees) {
        string line = to_string(emp.num) + " " + emp.name + " " + to_string(emp.hours) + " " + to_string(emp.hours * paymentRate) + "\n";
        DWORD bytesWritten = 0; // Инициализация переменной
        // Приводим line.size() к DWORD
        WriteFile(hOutFile, line.c_str(), static_cast<DWORD>(line.size()), &bytesWritten, NULL);
    }

    CloseHandle(hFile);
    CloseHandle(hOutFile);

    cout << "Report finished" << endl;
}

#define NOMINMAX
#include <windows.h>
#include <string>
#include <iostream>
#include <limits>
using namespace std;

// Объявления функций
void createEmployeeFile(const wstring& outputFileName, int numEmployees);
void generateReport(const wstring& inputFileName, const wstring& outputFileName, int paymentRate);

int main()
{
    wstring employeeBinFileName;
    unsigned int numOfEmployees;
    wcout << L"Enter name of binary file that utility Creator will make" << endl;
    wcin >> employeeBinFileName;

    while (true)
    {
        cout << "Enter amount of employees" << endl;
        if (cin >> numOfEmployees)
            break;
        else
        {
            cout << "Invalid input. Please enter a valid natural number." << endl;
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }

    // Создание бинарного файла
    createEmployeeFile(employeeBinFileName, numOfEmployees);

    wcout << L"Enter name of text file:" << endl;
    wstring reportFileName;
    wcin >> reportFileName;
    unsigned int paymentRate;

    while (true)
    {
        cout << "Enter payment rate: " << endl;
        if (cin >> paymentRate)
            break;
        else
        {
            cout << "Invalid input. Please enter a valid natural number." << endl;
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }

    // Генерация отчета
    generateReport(employeeBinFileName, reportFileName, paymentRate);

    return 0;
}

#include <windows.h>
#include <iostream>
using namespace std;

struct list {
	int n;
	int* arr;
	int min;
	int max;
	int average;
};

DWORD WINAPI min_max(LPVOID l) {
	list* work = (list*)l;
	int min_element = INT_MAX;
	int max_element = INT_MIN;
	for (int i = 0; i < work->n; i++) {
		min_element = min(min_element, work->arr[i]);
		Sleep(7);
		max_element = max(max_element, work->arr[i]);
		Sleep(7);
	}

	cout << "Minimum: " << min_element << ". Maximum: " << max_element << ".\n";
	work->min = min_element;
	work->max = max_element;
	return 0;
}

DWORD WINAPI average(LPVOID l) {
	list* work = (list*)l;
	int sum = 0;
	for (int i = 0; i < work->n; i++) {
		sum += work->arr[i];
		Sleep(12);
	}
	work->average = sum / work->n;
	cout << "Average is " << work->average << ".\n";

	return 0;
}

DWORD WINAPI main_thread(LPVOID) {
	cout << "Enter size of the array: ";
	list* temp = new list;
	cin >> temp->n;
	temp->arr = new int[temp->n];
	cout << "Enter the elements of the array: ";
	for (int i = 0; i < temp->n; i++) {
		cin >> temp->arr[i];
	}

	HANDLE min_max_thread;
	DWORD ID_min_max_thread;

	min_max_thread = CreateThread(NULL, 0, min_max, (void*)temp, 0, &ID_min_max_thread);

	if (min_max_thread == NULL)
		return GetLastError();

	WaitForSingleObject(min_max_thread, INFINITE);
	CloseHandle(min_max_thread);

	HANDLE average_thread;
	DWORD ID_average_thread;

	average_thread = CreateThread(NULL, 0, average, (void*)temp, 0, &ID_average_thread);

	if (average_thread == NULL)
		return GetLastError();

	WaitForSingleObject(average_thread, INFINITE);
	CloseHandle(average_thread);

	for (int i = 0; i < temp->n; i++) {
		if (temp->arr[i] == temp->max) {
			temp->arr[i] = temp->average;
		}
		if (temp->arr[i] == temp->min) {
			temp->arr[i] = temp->average;
		}
	}

	cout << "The result\n";
	for (int i = 0; i < temp->n; i++) {
		cout << temp->arr[i] << " ";
	}

	return 0;
}

int main()
{
	HANDLE hThread;
	DWORD IDThread;
	hThread = CreateThread(NULL, 0, main_thread, 0, 0, &IDThread);
	if (hThread == NULL)
		return GetLastError();
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
} 
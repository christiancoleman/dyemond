#include "pch.h"
#include "Memory.h"

using namespace std;

int main()
{
    cout << "Hello World!\n"; 

	Memory m = Memory();

	DWORD ffPID = m.getGamePID();
	HANDLE ff = m.openProcess();
	DWORD base = m.getBaseAddress(ff);
	
	cout << "Process ID: " << ffPID << endl;
	cout << "HANDLE to process: " << ff << endl;
	cout << "Base address of process: 0x" << hex << base << endl;
}
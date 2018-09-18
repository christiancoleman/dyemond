#include "pch.h"
#include "Memory.h"

/*
	Used:
		* Game Hacking - Developing Autonomous Bots for Online Games
*/

/////////////////////////////////////////////////////////////////////////
// public ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/*
	Page 120 of Game Hacking book
	'Opening the Game's Process Identifier'
*/
DWORD Memory::getGamePID() {
	HWND myWindow = FindWindow(NULL, L"FINAL FANTASY XIV"); // TODO: use public variable
	DWORD PID;
	GetWindowThreadProcessId(myWindow, &PID);
	return PID;
}

/*
	Page 121-122 of Game Hacking book
	'Working with OpenProcess()'
*/
HANDLE Memory::openProcess() {
	DWORD PID = this->getGamePID();
	HANDLE process = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, PID);
	if (process == INVALID_HANDLE_VALUE) {
		printf("Failed to open PID %d, error code %d", PID, GetLastError());
		return NULL;
	}
	return process;
}

/*
	Page 129-130 of Game Hacking book
	'Bypassing ASLR in Production'
*/
DWORD Memory::getBaseAddress(HANDLE process) {
	DWORD newBase;

	// get the address of kernel32.dll
	HMODULE kernel32 = GetModuleHandle(L"kernel32.dll");

	// get the address of GetModuleHandle()
	LPVOID getModuleHandlePtr = GetProcAddress(kernel32, "GetModuleHandleA");
	if (!getModuleHandlePtr) {
		getModuleHandlePtr = GetProcAddress(kernel32, "GetModuleHandleW");
	}

	// create thread
	HANDLE thread = CreateRemoteThread(
		process,
		NULL,
		NULL,
		(LPTHREAD_START_ROUTINE)getModuleHandlePtr,
		NULL,
		NULL,
		NULL
	);

	// let the thread finish
	WaitForSingleObject(thread, INFINITE);

	// get the exit code
	GetExitCodeThread(thread, &newBase);

	// clean up the thread handle
	CloseHandle(thread);

	return newBase;
}

/*
	Page 123-124 of Game Hacking book
	'Writing Templated Memory Access Functions'
*/
template<typename T>
T Memory::readMemory(HANDLE process, LPVOID address) {
	T val;
	ReadProcessMemory(process, address, &val, sizeof(T), NULL);
	return val;
}

/*
	Page 123-124 of Game Hacking book
	'Writing Templated Memory Access Functions'
*/
template<typename T>
void Memory::writeMemory(HANDLE process, LPVOID address, T value) {
	WriteProcessMemory(process, address, &value, sizeof(T), NULL);
}

/*
	Page 127 of Game Hacking book
	'Changing Memory Protection'
*/
template<typename T>
DWORD Memory::protectMemory(HANDLE process, LPVOID address, DWORD newProtection) {
	DWORD oldProtection;
	VirtualProtectEx(process, address, sizeof(T), newProtection, &oldProtection);
	return oldProtection;
}

/*
	Page 128-129 of Game Hacking book
	'Bypassing ASLR in Production'
*/
DWORD Memory::rebase(DWORD address, DWORD newBase) {
	DWORD diff = address - 0x400000;
	return diff + newBase;
}

/////////////////////////////////////////////////////////////////////////
// private //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////


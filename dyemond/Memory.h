#pragma once

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
using namespace std;

class Memory {

public:

	/*
		Manually set to window title of game for now
	*/
	wstring GAME_NAME = L"FINAL FANTASY XIV";

	/*

	*/
	DWORD getGamePID();

	/*

	*/
	HANDLE openProcess();

	/*
			
	*/
	DWORD getBaseAddress(HANDLE);

	/*
		
	*/
	template<typename T>
	T readMemory(HANDLE, LPVOID);

	/*
			
	*/
	template<typename T>
	void writeMemory(HANDLE, LPVOID, T);

	/*
			
	*/
	template<typename T>
	DWORD protectMemory(HANDLE, LPVOID, DWORD);

	/*
			
	*/
	DWORD rebase(DWORD, DWORD);

private:

		

};
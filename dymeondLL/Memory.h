#pragma once

class Memory
{
public:

	DWORD BaseAddress = NULL;

	Memory();
	~Memory();

	/*
		
	*/
	DWORD getBaseAddress();

	/*
		
	*/
	template<typename T>
	T readMemory(DWORD);

	/*
	
	*/
	template<typename T>
	T* pointMemory(DWORD);

	/*
	
	*/
	template<typename T>
	void writeMemory(DWORD, T);

	/*
	
	*/
	template<typename T>
	DWORD protectMemory(DWORD, DWORD);

	/*
	
	*/
	void NOPExample();
	
	/*
	
	*/
	void callHookExample();
	
	/*
	
	*/
	void VFHookExample();
	
	/*
	
	*/
	void IATHookExample();

private:

	IMAGE_DOS_HEADER getDosHeader();

};


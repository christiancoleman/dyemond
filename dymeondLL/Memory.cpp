#include "stdafx.h"
#include "Memory.h"

/*
	Used:
		* Game Hacking - Developing Autonomous Bots for Online Games
*/

/////////////////////////////////////////////////////////////////////////
// public ///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

Memory::Memory()
{
}

Memory::~Memory()
{
}

/*
	Page 160 of Game Hacking book
*/
DWORD Memory::getBaseAddress() {
	if (this->BaseAddress == NULL) {
		this->BaseAddress = (DWORD)GetModuleHandle(NULL);
	}
	return this->BaseAddress;
}



/*
	
*/
template<typename T>
T Memory::readMemory(DWORD address)
{
	return *((T*)address);
}

template<typename T>
T* pointMemory(DWORD address)
{
	return ((T*)address);
}

template<typename T>
void Memory::writeMemory(DWORD address, T value)
{
	*((T*)address) = value;
}

template<typename T>
DWORD Memory::protectMemory(DWORD address, DWORD protection)
{
	DWORD oldProt;
	VirtualProtect((LPVOID)address, sizeof(T), protection, &oldProt);
	return oldProt;
}

void Memory::NOPExample() {

}

void Memory::callHookExample() {

}

void Memory::VFHookExample() {

}

void Memory::IATHookExample() {

}

/////////////////////////////////////////////////////////////////////////
// private //////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

int Memory::getDosHeader() {
	return NULL;
}

#include <iostream>

#include "proc.h"

int main()
{

	const char *windowName = "Counter-Strike: Global Offensive";
	const char *moduleName = "client.dll";

	DWORD processId = GetProcessId(windowName);;
	std::cout << "Process Id = " << processId << std::endl;

	uintptr_t moduleAdrress = GetModuleAddress(processId, moduleName);
	std::cout << "Module address = " << moduleAdrress << std::endl;

}
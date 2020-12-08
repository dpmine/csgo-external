#include "proc.h" //Include your header

DWORD GetProcessId(const char *windowName)
{
	DWORD processId = 0;
	uint32_t session = 0;

	HWND FindProcessWindow;

	do
	{
		FindProcessWindow = FindWindowA(NULL, windowName);
		GetWindowThreadProcessId(FindProcessWindow, &processId);

		if (processId == NULL)
		{
			std::cout << "Failed to get processId.\n";
			return 0;
		}

		std::cout << "Process Id found! Returning -> " << processId;
		return processId;

	} while (!FindProcessWindow && session <= 180);

	session++;
	Sleep(1000);

	return 0;
}

uintptr_t GetModuleAddress(DWORD processId, const char *moduleName)
{
	std::cout << "Getting module address.\n";
	uintptr_t modAddr = 0;
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

	if (hProcess == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to snapshot process modules.\n";
		return 0;
	}

	MODULEENTRY32 entry;
	entry.dwSize = sizeof(entry);

	if (Module32First(hProcess, &entry))
	{
		std::cout << "MODULE32FIRST Sucessfully copied to the ENTRY buffer.\n";
		do
		{
			if (!strcmp(moduleName, entry.szModule))
			{
				modAddr = (uintptr_t)entry.modBaseAddr;
				std::cout << "Returned module adrress.\n";
			}

		} while (Module32Next(hProcess, &entry));
	}

	CloseHandle(hProcess);

	if (modAddr == 0)
	{
		std::cout << "Failed to get module address.\n";
		return 0;
	}

	return modAddr;
}

uintptr_t ResolveDMAAdy(HANDLE hProcess, uintptr_t ptr, std::vector<unsigned int> offset)
{
	uintptr_t addr = ptr;
	for (int i = 0; i <= offset.size(); i++)
	{
		bool memRead = ReadProcessMemory(hProcess, (BYTE *)addr, &addr, sizeof(addr), NULL);
		if (!memRead)
		{
			std::cout << "Failed to resolve offsets.\n";
		}

		addr += offset[i];
	}

	return addr;
}
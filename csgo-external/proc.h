#pragma once

//We need this 3 librarys ->
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

DWORD GetProcessId(const char *windowName); 
uintptr_t GetModuleAddress(DWORD processId, const char *moduleName);
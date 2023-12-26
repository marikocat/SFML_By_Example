#pragma once

#define RUNNING_WINDOWS
#include <iostream>
#include <string>
#include <algorithm>

namespace Utils
{
#ifdef RUNNING_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <pathcch.h>
	inline std::string GetWorkingDirectory()
	{
		HMODULE hModule = GetModuleHandle(nullptr);
		if (hModule) {
			char path[256];
			GetModuleFileNameA(hModule, path, sizeof(path));
			std::string s(path);
			s = s.substr(0, s.find_last_of("\\/"));
			s += "\\";
			return s;
		}
		return "";
	}
#elif defined RUNNING_LINUX
#include <unistd.h>
	inline std::string GetWorkingDirectory()
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) != nullptr)
		{
			return std::string(cwd) + std::string("/");
		}
		return "";
	}
#endif // RUNNING_WINDOWS
}
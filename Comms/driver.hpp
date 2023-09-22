#pragma once
#include <TlHelp32.h>
#include "librarys.hpp"
#include "../AntiDebug/CallStack-Spoofer.h"

class _driver
{
private:
	typedef __int64(*NtUserFunction)(uintptr_t);
	NtUserFunction nt_user_function = 0;
	enum REQUEST_TYPE : int
	{
		NONE,
		BASE,
		WRITE,
		READ
	};
	typedef struct _DRIVER_REQUEST
	{
		
		REQUEST_TYPE type;
		HANDLE pid;
		PVOID address;
		PVOID buffer;
		SIZE_T size;
		PVOID base;
	} DRIVER_REQUEST, *PDRIVER_REQUEST;
	void send_request(PDRIVER_REQUEST out)
	{
		SPOOF_FUNC;
		RtlSecureZeroMemory(out, 0);
		nt_user_function(reinterpret_cast<uintptr_t>(out));
	}
public:
	int process_id;
	uintptr_t rootAddress;
	DWORD get_process_id(LPCTSTR process_name)
	{
		SPOOF_FUNC;
		PROCESSENTRY32 pt{};
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt))
		{
			do {
				if (!lstrcmpi(pt.szExeFile, process_name))
				{
					CloseHandle(hsnap);
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);
		return 0;
	}
	bool setup()
	{
		SPOOF_FUNC;
		nt_user_function = reinterpret_cast<NtUserFunction>(GetProcAddress(librarys::user32, "NtUserRegisterErrorReportingDialog"));
		if (!nt_user_function)
		{
			nt_user_function = reinterpret_cast<NtUserFunction>(GetProcAddress(librarys::win32u, "NtUserRegisterErrorReportingDialog"));
			if (!nt_user_function) return false;
		}
		return true;
	}
	uintptr_t get_base_address()
	{
		SPOOF_FUNC;
		DRIVER_REQUEST out{};
		out.type = BASE;
		out.pid = (HANDLE)process_id;
		send_request(&out);
		return (uintptr_t)out.base;
	}
	void writem(PVOID address, PVOID buffer, DWORD size)
	{
		SPOOF_FUNC;
		DRIVER_REQUEST out{};
		out.type = WRITE;
		out.pid = (HANDLE)process_id;
		out.address = address;
		out.buffer = buffer;
		out.size = size;
		send_request(&out);
	}
	void readm(PVOID address, PVOID buffer, DWORD size)
	{
		SPOOF_FUNC;
		DRIVER_REQUEST out{};
		out.type = READ;
		out.pid = (HANDLE)process_id;
		out.address = address;
		out.buffer = buffer;
		out.size = size;
		send_request(&out);
	}
	template<typename T> void write(uintptr_t address, T value)
	{
		SPOOF_FUNC;
		writem((PVOID)address, &value, sizeof(T));
	}
	template<typename T> T read(uintptr_t address)
	{
		SPOOF_FUNC;
		T buffer{};
		readm((PVOID)address, &buffer, sizeof(T));
		return buffer;
	}
};
_driver driver;
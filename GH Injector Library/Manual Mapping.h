#pragma once

#include "VEH Shell.h"

#define RELOC_FLAG86(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_HIGHLOW)
#define RELOC_FLAG64(RelInfo) ((RelInfo >> 0x0C) == IMAGE_REL_BASED_DIR64)

#ifdef _WIN64
#define RELOC_FLAG RELOC_FLAG64
#else
#define RELOC_FLAG RELOC_FLAG86
#endif

#define MIN_SHIFT_OFFSET	0x100
#define MAX_SHIFT_OFFSET	0x1000

using f_DLL_ENTRY_POINT	= BOOL(WINAPI *)(HINSTANCE hDll, DWORD dwReason, void * pReserved);

//list to track imports and unload on failure
typedef struct _MM_DEPENDENCY_RECORD
{
	struct _MM_DEPENDENCY_RECORD * Next;
	struct _MM_DEPENDENCY_RECORD * Prev;
	HANDLE DllHandle;
} MM_DEPENDENCY_RECORD, * PMM_DEPENDENCY_RECORD;

namespace MMAP_NATIVE
{
	using namespace NATIVE;

	ALIGN struct MODULE_DEPENDENCY_LIST_ENTRY
	{
		ALIGN MODULE_DEPENDENCY_LIST_ENTRY * Next;
		ALIGN HINSTANCE hModule;
		ALIGN DWORD SizeOfImage;
	};

	ALIGN struct MANUAL_MAPPING_FUNCTION_TABLE
	{
		ALIGN NT_FUNC_LOCAL(NtOpenFile);
		ALIGN NT_FUNC_LOCAL(NtReadFile);
		ALIGN NT_FUNC_LOCAL(NtClose);

		ALIGN NT_FUNC_LOCAL(NtSetInformationFile);
		ALIGN NT_FUNC_LOCAL(NtQueryInformationFile);

		ALIGN NT_FUNC_LOCAL(NtAllocateVirtualMemory);
		ALIGN NT_FUNC_LOCAL(NtProtectVirtualMemory);
		ALIGN NT_FUNC_LOCAL(NtFreeVirtualMemory);

		ALIGN NT_FUNC_LOCAL(NtCreateSection);
		ALIGN NT_FUNC_LOCAL(NtMapViewOfSection);

		ALIGN NT_FUNC_LOCAL(memmove);
		ALIGN NT_FUNC_LOCAL(RtlZeroMemory);
		ALIGN NT_FUNC_LOCAL(RtlAllocateHeap);
		ALIGN NT_FUNC_LOCAL(RtlFreeHeap);

		ALIGN NT_FUNC_LOCAL(LdrpLoadDll);
		ALIGN NT_FUNC_LOCAL(LdrpLoadDllInternal);
		ALIGN NT_FUNC_LOCAL(LdrGetProcedureAddress);

		ALIGN NT_FUNC_LOCAL(LdrUnloadDll);

		ALIGN NT_FUNC_LOCAL(RtlAnsiStringToUnicodeString);

		ALIGN NT_FUNC_LOCAL(LdrpPreprocessDllName);
		ALIGN NT_FUNC_LOCAL(RtlInsertInvertedFunctionTable);
#ifdef _WIN64
		ALIGN NT_FUNC_LOCAL(RtlAddFunctionTable);
#endif
		ALIGN NT_FUNC_LOCAL(LdrpHandleTlsData);

		ALIGN NT_FUNC_LOCAL(LdrLockLoaderLock);
		ALIGN NT_FUNC_LOCAL(LdrUnlockLoaderLock);

		ALIGN NT_FUNC_LOCAL(LdrProtectMrdata);

		ALIGN NT_FUNC_LOCAL(RtlAddVectoredExceptionHandler);
		ALIGN NT_FUNC_LOCAL(RtlRemoveVectoredExceptionHandler);

		ALIGN NT_FUNC_LOCAL(LdrpModuleBaseAddressIndex);
		ALIGN NT_FUNC_LOCAL(LdrpMappingInfoIndex);
		ALIGN NT_FUNC_LOCAL(LdrpHeap);
		ALIGN NT_FUNC_LOCAL(LdrpInvertedFunctionTable);
		ALIGN NT_FUNC_LOCAL(LdrpDefaultPath);
		ALIGN NT_FUNC_LOCAL(LdrpTlsList);

		ALIGN void * pLdrpHeap;

		MANUAL_MAPPING_FUNCTION_TABLE();
	};
	
	ALIGN struct MANUAL_MAPPING_DATA
	{
		ALIGN HINSTANCE	hRet	= NULL;
		ALIGN DWORD		Flags	= NULL;
		ALIGN NTSTATUS	ntRet	= STATUS_SUCCESS;

		ALIGN WORD ShiftOffset = 0;

		ALIGN UNICODE_STRING DllPath{ 0 };
		ALIGN wchar_t szPathBuffer[MAX_PATH]{ 0 };

		ALIGN UNICODE_STRING DllName{ 0 };
		ALIGN wchar_t szNameBuffer[MAX_PATH]{ 0 };

		ALIGN wchar_t NtPathPrefix[8] = L"\\??\\\0\0\0";

		ALIGN DWORD OSVersion		= 0;
		ALIGN DWORD OSBuildNumber	= 0;

		ALIGN BYTE * pVEHShell		= nullptr;
		ALIGN DWORD VEHShellSize	= 0;
		ALIGN HANDLE hVEH			= nullptr;

		ALIGN MANUAL_MAPPING_FUNCTION_TABLE f;
	};

	DWORD ManualMap(const wchar_t * szDllFile, HANDLE hTargetProc, LAUNCH_METHOD Method, DWORD Flags, HINSTANCE & hOut, DWORD Timeout, ERROR_DATA & error_data);
}

#ifdef _WIN64

namespace MMAP_WOW64
{
	using namespace WOW64;

	ALIGN_86 struct MANUAL_MAPPING_FUNCTION_TABLE_WOW64
	{
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtOpenFile);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtReadFile);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtClose);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtSetInformationFile);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtQueryInformationFile);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtAllocateVirtualMemory);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtProtectVirtualMemory);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtFreeVirtualMemory);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtCreateSection);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(NtMapViewOfSection);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(memmove);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlZeroMemory);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlAllocateHeap);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlFreeHeap);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpLoadDll);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpLoadDllInternal);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrGetProcedureAddress);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrUnloadDll);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlAnsiStringToUnicodeString);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpPreprocessDllName);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlInsertInvertedFunctionTable);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpHandleTlsData);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrLockLoaderLock);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrUnlockLoaderLock);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrProtectMrdata);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlAddVectoredExceptionHandler);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(RtlRemoveVectoredExceptionHandler);

		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpModuleBaseAddressIndex);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpMappingInfoIndex);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpHeap);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpInvertedFunctionTable);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpDefaultPath);
		ALIGN_86 WOW64_FUNCTION_POINTER_LOCAL(LdrpTlsList);

		ALIGN_86 DWORD pLdrpHeap;

		MANUAL_MAPPING_FUNCTION_TABLE_WOW64();
	};

	ALIGN_86 struct MANUAL_MAPPING_DATA_WOW64
	{
		ALIGN_86 DWORD	hRet	= NULL;
		ALIGN_86 DWORD	Flags	= NULL;
		ALIGN_86 DWORD	ntRet	= STATUS_SUCCESS;

		ALIGN_86 WORD ShiftOffset = 0;

		ALIGN_86 UNICODE_STRING_32 DllPath{ 0 };
		ALIGN_86 wchar_t szPathBuffer[MAX_PATH]{ 0 };

		ALIGN_86 UNICODE_STRING_32 DllName{ 0 };
		ALIGN_86 wchar_t szNameBuffer[MAX_PATH]{ 0 };

		ALIGN_86 wchar_t NtPathPrefix[8] = L"\\??\\\0\0\0";

		ALIGN_86 DWORD OSVersion		= 0;
		ALIGN_86 DWORD OSBuildNumber	= 0;

		ALIGN_86 DWORD pVEHShell	= 0;
		ALIGN_86 DWORD VEHShellSize = 0;
		ALIGN_86 DWORD hVEH			= 0;

		ALIGN_86 MANUAL_MAPPING_FUNCTION_TABLE_WOW64 f;
	};

	DWORD ManualMap_WOW64(const wchar_t * szDllFile, HANDLE hTargetProc, LAUNCH_METHOD Method, DWORD Flags, HINSTANCE & hOut, DWORD Timeout, ERROR_DATA & error_data);
}

#endif
#pragma once
#include <Windows.h>

#define STATUS_SUCCESS 0

EXTERN_C NTSTATUS ANtAVM (
	HANDLE ProcessHandle,
	PVOID* BaseAddress,
	ULONG_PTR ZeroBits,
	PSIZE_T RegionSize,
	ULONG AllocationType,
	ULONG Protect
);

EXTERN_C NTSTATUS ANtWVM (
	HANDLE hProcess,
	PVOID lpBaseAddress,
	PVOID lpBuffer,
	SIZE_T NumberOfBytesToRead,
	PSIZE_T NumberOfBytesRead
);

EXTERN_C NTSTATUS ANtPVM (
	HANDLE ProcessHandle,
	PVOID* BaseAddress,
	SIZE_T* NumberOfBytesToProtect,
	ULONG NewAccessProtection,
	PULONG OldAccessProtection
);

EXTERN_C NTSTATUS ANtCTE (
	HANDLE* pHandle, 
	ACCESS_MASK DesiredAccess, 
	PVOID pAttr, 
	HANDLE hProc, 
	PVOID pFunc,
	PVOID pArg,
	ULONG Flags, 
	SIZE_T ZeroBits, 
	SIZE_T StackSize, 
	SIZE_T MaxStackSize, 
	PVOID pAttrListOut
);


#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "NtThings.h"

#include <iostream>
#include <tchar.h>
#include <list>
#include <vector>
#include <string>
#include <Psapi.h>
#include <VersionHelpers.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

using std::cout;
using std::cin;
using std::list;
using std::vector;

const int XOR_KEY{ 8 };

const std::vector<LPVOID> VC_PREF_BASES{ (void*)0x00000000DDDD0000,
                                       (void*)0x0000000010000000,
                                       (void*)0x0000000021000000,
                                       (void*)0x0000000032000000,
                                       (void*)0x0000000043000000,
                                       (void*)0x0000000050000000,
                                       (void*)0x0000000041000000,
                                       (void*)0x0000000042000000,
                                       (void*)0x0000000040000000,
                                       (void*)0x0000000022000000 };

// Helpers.cpp
LPVOID GetSuitableBaseAddress(HANDLE hProc, DWORD page_size, DWORD alloc_gran, DWORD vm_resv_c);
unsigned char* ReadProcessBlob(const char* sc_filename, DWORD* sc_size);
void DelayShowProgress(double percentage, int step, int step_time, int tpid, int time_needed, int vmbase);
void EnableAnsiSupport();
void PlayHeader();

const char PBAR[]{ "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||" };
const int  PBAR_WDH{ 60 };
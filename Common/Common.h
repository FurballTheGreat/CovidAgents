#pragma once
#include<stdint.h>
#ifdef _MSC_VER
#define WIN32_NO_STATUS
#include <Windows.h>
#undef WIN32_NO_STATUS
#include "ntstatus.h"
#else
typedef uint32_t DWORD;
typedef uint8_t BYTE;
typedef BYTE* PBYTE;
typedef uint8_t* PUCHAR;


#endif
#include <random>
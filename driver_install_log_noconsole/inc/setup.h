#pragma once
#include "stdafx.h"

enum WINDOWS_BITS_WIDTH
{
	WINDOWS_32BITS,
	WINDOWS_64BITS
};

enum WINDOWS_VERSION
{
	WINDOWS_XP,
	WINDOWS_VISTA,
	WINDOWS_7,
	WINDOWS_8,
	WINDOWS_8_1,
	WINDOWS_10,
	OTHER_VERSION
};

BOOL IsDeviceInstallInProgress();
BOOL UpdateDriver(TCHAR* inf_path, TCHAR* inf_name_out);
int UpdateDriver();
WINDOWS_VERSION GetSystemVersion();
WINDOWS_BITS_WIDTH GetSystemBits();

BOOL UninstallDriver(TCHAR* inf_name);
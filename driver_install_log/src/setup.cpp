#include "stdafx.h"
#include "setup.h"

#include "setupapi.h"
#pragma comment(lib, "setupapi.lib")

#include <cfgmgr32.h>

#include <iostream>
#include <string>

#include "VersionHelpers.h"



#include "spdlog/spdlog.h"
using namespace std;

BOOL IsDeviceInstallInProgress()
{
	return !(CMP_WaitNoPendingInstallEvents(0) == WAIT_OBJECT_0);
}

BOOL UpdateDriver(TCHAR* inf_path, TCHAR* inf_name_out)
{
	
	while (IsDeviceInstallInProgress());
	//TCHAR* inf_path = _T(".\\Drivers\\Win81\\x64\\cyusb3.inf");
	//PCSTR inf_path = "D:\\1project\\usb_camera_034_show_version\\usb3_camera_version_0.6_fifo_034\\driver_install\\Drivers\\Win81\\x64\\cyusb3.inf";
	//if (FALSE == SetupCopyOEMInf(inf_path, NULL, SPOST_PATH, SP_COPY_NOOVERWRITE, NULL, 0, NULL, NULL))
	TCHAR path1[MAX_PATH] = {0};
	TCHAR *path2;
	if (FALSE == SetupCopyOEMInf(inf_path, NULL, SPOST_PATH, SP_COPY_NOOVERWRITE, path1, MAX_PATH, NULL, &path2))
	{
		DWORD error = GetLastError();
		if (error == ERROR_FILE_EXISTS)
		{
			spdlog::get("driver_install_info")->info("the driver file has existed, so succeeded");
			//cout << "File has been existed and succeed" << endl;
			//_tprintf(_T("the oem name is: %s\n"), path2);
			spdlog::get("driver_install_info")->info("the oem name is: \n" + string(path2));
			//cout << path2;
			//printf("the file name is: %s", path2);
			_tcscpy_s(inf_name_out, MAX_PATH, path2);
			return TRUE;
		}
		else
		{
			spdlog::get("driver_install_info")->info("install failed, ");
			spdlog::get("driver_install_info")->info("the error code is: " + to_string(error));
			//cout << "install failed, ";
			//cout << "the error code is: " << error << endl;
			return FALSE;
		}
			
	}
	else
	{
		spdlog::get("driver_install_info")->info("install succeeded\n");
		spdlog::get("driver_install_info")->info("the oem name is: " + string(path2) + "\n");
		//_tprintf(_T("the oem name is: %s\n"), path2);
		_tcscpy_s(inf_name_out, MAX_PATH, path2);

		return TRUE;
	}
}


BOOL UninstallDriver(TCHAR* path_name)
{
	//while (IsDeviceInstallInProgress());

	if (!SetupUninstallOEMInf(path_name,
		SUOI_FORCEDELETE,
		NULL))
	{
		DWORD error = GetLastError();
		if (error == ERROR_INF_IN_USE_BY_DEVICES)
		{
			spdlog::get("driver_install_info")->info("the device is being used and can't be deleted\n");
			//cout << "the device is being used and can't be deleted" << endl;
		}
		else if (error == ERROR_NOT_AN_INSTALLED_OEM_INF)
		{
			spdlog::get("driver_install_info")->info("can't find the oem file\n");
			//cout << "can't find the oem file" << endl;
		}
		else
		{
			spdlog::get("driver_install_info")->info("the uninstall failed and the error code is " + to_string(error));
			//cout << "the uninstall failed, ";
			//cout << "the error code is: " << error << endl;
		}

		return FALSE;
	}
	else
	{
		spdlog::get("driver_install_info")->info("uninstall succeeded");
		//cout << "uninstall succeeded" << endl;
		return TRUE;
	}
}


// 安全的取得真实系统信息  
VOID SafeGetNativeSystemInfo(__out LPSYSTEM_INFO lpSystemInfo)
{
	if (NULL == lpSystemInfo)    return;
	typedef VOID(WINAPI *LPFN_GetNativeSystemInfo)(LPSYSTEM_INFO lpSystemInfo);
	LPFN_GetNativeSystemInfo fnGetNativeSystemInfo = (LPFN_GetNativeSystemInfo)GetProcAddress(GetModuleHandle(_T("kernel32")), "GetNativeSystemInfo");
	if (NULL != fnGetNativeSystemInfo)
	{
		fnGetNativeSystemInfo(lpSystemInfo);
	}
	else
	{
		GetSystemInfo(lpSystemInfo);
	}
}

// 获取操作系统位数  
WINDOWS_BITS_WIDTH GetSystemBits()
{
	SYSTEM_INFO si;
	SafeGetNativeSystemInfo(&si);
	if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 ||
		si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)
	{
		return WINDOWS_64BITS;
	}
	return WINDOWS_32BITS;
}



WINDOWS_VERSION GetSystemVersion()
{
	if (IsWindows10OrGreater())
	{
		return WINDOWS_10;
	}
	else if (IsWindows8Point1OrGreater())
	{
		return WINDOWS_8_1;
	}
	else if (IsWindows8OrGreater())
	{
		return WINDOWS_8;
	}
	else if (IsWindows7OrGreater())
	{
		return WINDOWS_7;
	}
	else if (IsWindowsVistaOrGreater())
	{
		return WINDOWS_VISTA;
	}
	else if (IsWindowsXPOrGreater())
	{
		return WINDOWS_XP;
	}
	else
	{
		return OTHER_VERSION;
	}
}

int UpdateDriver()
{
	TCHAR path[MAX_PATH] = {0};
	GetModuleFileName(NULL, path, MAX_PATH);
	*(_tcsrchr(path, _T('\\'))) = 0;
	string msg(path);
	_tcscat_s(path, MAX_PATH, _T("\\Drivers\\"));
	

	//日志初始化
	//spdlog::set_async_mode(4096); 
	auto logger = spdlog::basic_logger_st("driver_install_info", msg + "\\driverlog.txt");

	spdlog::get("driver_install_info")->info("the driver files' directory is " + msg);
	
	
	//_tcscat_s(path, _T("winxp"));
	
	switch (GetSystemVersion())
	{
	case OTHER_VERSION:
		_tcscat_s(path, MAX_PATH, _T("wxp\\"));
		msg = "before winxp or windows server \n";
		//cout << "before winxp or windows server " << endl;
		break;
	case WINDOWS_XP:
		_tcscat_s(path, MAX_PATH, _T("wxp\\"));
		msg = "winxp ";
		//cout << "winxp ";
		break;
	case WINDOWS_VISTA:
		_tcscat_s(path, MAX_PATH, _T("vista\\"));
		msg = "vista ";
		//cout << "vista ";
		break;
	case WINDOWS_7:
		_tcscat_s(path, MAX_PATH, _T("Win7\\"));
		//cout << "win7 ";
		msg = "win7 ";
		break;
	case WINDOWS_8:
		_tcscat_s(path, MAX_PATH, _T("Win8\\"));
		msg = "win8 ";
		//cout << "win8 ";
		break;
	case WINDOWS_8_1:
		_tcscat_s(path, MAX_PATH, _T("Win81\\"));
		msg = "win8.1 ";
		//cout << "win8.1 ";
		break;
	case WINDOWS_10:
		_tcscat_s(path, MAX_PATH, _T("Win10\\"));
		msg = "win10 ";
		//cout << "win10 ";
		break;
	default:
		msg = "can't find related windows version\n";
		//cout << "can't find related windows version" << endl;
		break;
	}

	switch (GetSystemBits())
	{
	case WINDOWS_32BITS:
		_tcscat_s(path, MAX_PATH, _T("x86\\cyusb3.inf"));
		msg += "32bits system\n";
		//cout << "32bits system" << endl;
		break;
	case WINDOWS_64BITS:
		_tcscat_s(path, MAX_PATH, _T("x64\\cyusb3.inf"));
		msg += "64bits system\n";
		//cout << "64bits system" << endl;
		break;
	default:
		msg += "can't find related machine's drivers of other bits width\n";
		//cout << "can't find related machine's drivers of other bits width" << endl;
		break;
	}

	spdlog::get("driver_install_info")->info(msg);
	msg = "";

	TCHAR cur_dir[MAX_PATH] = { 0 };
	GetCurrentDirectory(MAX_PATH, cur_dir);
	spdlog::get("driver_install_info")->info("the current dir is " + string(cur_dir));
	//_tprintf(_T("the current dir is: %s\n"), cur_dir);
	//_tprintf(_T("the .exe dir is: %s\n"), path);

	BOOL flag = FALSE;
	TCHAR inf_name[MAX_PATH] = { 0 };
	
	flag = UpdateDriver(path, inf_name);


	spdlog::drop("driver_install_info");
	return 0;
}


//WINDOWS_VERSION GetSystemName(/*TCHAR* osname*/)
//{
//	SYSTEM_INFO info;        //用SYSTEM_INFO结构判断64位AMD处理器   
//	GetSystemInfo(&info);    //调用GetSystemInfo函数填充结构   
//	OSVERSIONINFOEX os;
//	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
//
//	//osname = _T("unknown OperatingSystem.");
//
//	if (GetVersionEx((OSVERSIONINFO *)&os))
//	{
//		//下面根据版本信息判断操作系统名称   
//		switch (os.dwMajorVersion)//判断主版本号  
//		{
//		case 4:
//			return WINDOWS_9X;
//			break;
//
//		case 5:
//			//有其他系列的，但当做xp，因为只提供了xp的驱动
//			return WINDOWS_XP;
//			break;
//
//		case 6:
//			switch (os.dwMinorVersion)
//			{
//			case 0:
//				//有其他系列的，但只当做vista,因为只提供了vista的驱动
//				return WINDOWS_VISTA;
//				break;
//			case 1:
//				return WINDOWS_7;
//				break;
//			case 2:
//				return WINDOWS_8;
//				break;
//			case 3:
//				return WINDOWS_8_1;
//			}
//			break;
//
//		case 10:
//			return WINDOWS_10;
//		}
//	}//if(GetVersionEx((OSVERSIONINFO *)&os))  
//
//}

//void GetVersionMark(TCHAR* vmark)
//{
//	OSVERSIONINFOEX os;
//	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
//	vmark = _T("");
//
//	if (GetVersionEx((OSVERSIONINFO*)&os))
//	{
//		switch (os.dwMajorVersion)
//		{                //先判断操作系统版本   
//		case 5:
//			switch (os.dwMinorVersion)
//			{
//			case 0:                  //Windows 2000   
//				if (os.wSuiteMask == VER_SUITE_ENTERPRISE)
//					vmark = _T("Advanced Server");
//				break;
//			case 1:                  //Windows XP   
//				if (os.wSuiteMask == VER_SUITE_EMBEDDEDNT)
//					vmark = _T("Embedded");
//				else if (os.wSuiteMask == VER_SUITE_PERSONAL)
//					vmark = _T("Home Edition");
//				else
//					vmark = _T("Professional");
//				break;
//			case 2:
//				if (GetSystemMetrics(SM_SERVERR2) == 0
//					&& os.wSuiteMask == VER_SUITE_BLADE)  //Windows Server 2003   
//					vmark = _T("Web Edition");
//				else if (GetSystemMetrics(SM_SERVERR2) == 0
//					&& os.wSuiteMask == VER_SUITE_COMPUTE_SERVER)
//					vmark = _T("Compute Cluster Edition");
//				else if (GetSystemMetrics(SM_SERVERR2) == 0
//					&& os.wSuiteMask == VER_SUITE_STORAGE_SERVER)
//					vmark = _T("Storage Server");
//				else if (GetSystemMetrics(SM_SERVERR2) == 0
//					&& os.wSuiteMask == VER_SUITE_DATACENTER)
//					vmark = _T("Datacenter Edition");
//				else if (GetSystemMetrics(SM_SERVERR2) == 0
//					&& os.wSuiteMask == VER_SUITE_ENTERPRISE)
//					vmark = _T("Enterprise Edition");
//				else if (GetSystemMetrics(SM_SERVERR2) != 0
//					&& os.wSuiteMask == VER_SUITE_STORAGE_SERVER)
//					vmark = _T("Storage Server");
//				break;
//			}
//			break;
//
//		case 6:
//			switch (os.dwMinorVersion)
//			{
//			case 0:
//				if (os.wProductType != VER_NT_WORKSTATION
//					&& os.wSuiteMask == VER_SUITE_DATACENTER)
//					vmark = _T("Datacenter Server");
//				else if (os.wProductType != VER_NT_WORKSTATION
//					&& os.wSuiteMask == VER_SUITE_ENTERPRISE)
//					vmark = _T("Enterprise");
//				else if (os.wProductType == VER_NT_WORKSTATION
//					&& os.wSuiteMask == VER_SUITE_PERSONAL)  //Windows Vista  
//					vmark = _T("Home");
//				break;
//			}
//			break;
//		}
//	}
//}


//void GetSystemName(TCHAR* osname)
//{
//	SYSTEM_INFO info;        //用SYSTEM_INFO结构判断64位AMD处理器   
//	GetSystemInfo(&info);    //调用GetSystemInfo函数填充结构   
//	OSVERSIONINFOEX os;
//	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
//
//	osname = _T("unknown OperatingSystem.");
//
//	if (GetVersionEx((OSVERSIONINFO *)&os))
//	{
//		//下面根据版本信息判断操作系统名称   
//		switch (os.dwMajorVersion)//判断主版本号  
//		{
//		case 4:
//			switch (os.dwMinorVersion)//判断次版本号   
//			{
//			case 0:
//				if (os.dwPlatformId == VER_PLATFORM_WIN32_NT)
//					osname = _T("Microsoft Windows NT 4.0"); //1996年7月发布   
//				else if (os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
//					osname = _T("Microsoft Windows 95");
//				break;
//			case 10:
//				osname = _T("Microsoft Windows 98");
//				break;
//			case 90:
//				osname = _T("Microsoft Windows Me");
//				break;
//			}
//			break;
//
//		case 5:
//			switch (os.dwMinorVersion)   //再比较dwMinorVersion的值  
//			{
//			case 0:
//				osname = _T("Microsoft Windows 2000");//1999年12月发布  
//				break;
//
//			case 1:
//				osname = _T("Microsoft Windows XP");//2001年8月发布  
//				break;
//
//			case 2:
//				if (os.wProductType == VER_NT_WORKSTATION
//					&& info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
//				{
//					osname = _T("Microsoft Windows XP Professional x64 Edition");
//				}
//				else if (GetSystemMetrics(SM_SERVERR2) == 0)
//					osname = _T("Microsoft Windows Server 2003");//2003年3月发布   
//				else if (GetSystemMetrics(SM_SERVERR2) != 0)
//					osname = _T("Microsoft Windows Server 2003 R2");
//				break;
//			}
//			break;
//
//		case 6:
//			switch (os.dwMinorVersion)
//			{
//			case 0:
//				if (os.wProductType == VER_NT_WORKSTATION)
//					osname = _T("Microsoft Windows Vista");
//				else
//					osname = _T("Microsoft Windows Server 2008");//服务器版本   
//				break;
//			case 1:
//				if (os.wProductType == VER_NT_WORKSTATION)
//					osname = _T("Microsoft Windows 7");
//				else
//					osname = _T("Microsoft Windows Server 2008 R2");
//				break;
//			}
//			break;
//		}
//	}//if(GetVersionEx((OSVERSIONINFO *)&os))  
//
//}
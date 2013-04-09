#pragma once

#if defined(_WIN32) && !defined(__WINREGISTRY_H)
#define __WINREGISTRY_H

#include <string>
#include <fstream>
#include <cstdarg>
#include <cstdio>
#include <map>

#include <windows.h>

using namespace std;

class Registry
{
private:
	HKEY _hkey;

public:
	Registry();
	~Registry();

	bool Open(string key);
	void Close();

	bool Registry::Read(string valueName, string valueTypeName, void* value, DWORD* valueSize);
	bool ReadDword(string valueName, LPDWORD value);
};

Registry::Registry()
{
	_hkey = NULL;
}

Registry::~Registry()
{
	Close();
}

bool Registry::Open(string key)
{
	return (RegOpenKeyEx(HKEY_LOCAL_MACHINE, key.c_str(), 0, KEY_READ, &_hkey) == ERROR_SUCCESS);
}

bool Registry::Read(string valueName, string valueTypeName, void* value, DWORD* valueSize)
{
	map<string,DWORD> valuetypes;
	valuetypes["REG_SZ"] = REG_SZ;
	valuetypes["REG_DWORD"] = REG_DWORD;
	valuetypes["REG_QWORD"] = REG_QWORD;
	valuetypes["REG_EXPAND_SZ"] = REG_EXPAND_SZ;
	valuetypes["REG_MULTI_SZ"] = REG_MULTI_SZ;

	DWORD bufferLen = 4096;
	char* buffer = (char*)malloc(bufferLen);
	
	DWORD valuetype = valuetypes[valueTypeName];
	bool result = (RegQueryValueEx(_hkey, valueName.c_str(), NULL, &valuetype, (LPBYTE)buffer, &bufferLen) == ERROR_SUCCESS);
	if (result)
	{
		*valueSize = bufferLen;
		memcpy(value, buffer, bufferLen);
	}

	free(buffer);

	return result;
}

bool Registry::ReadDword(string valueName, LPDWORD value)
{
	DWORD valueType = REG_DWORD;

	DWORD bufferLen = sizeof(DWORD);
	DWORD* buffer = (DWORD*)malloc(bufferLen);
	
	bool result = (RegQueryValueEx(_hkey, valueName.c_str(), NULL, &valueType, (LPBYTE)buffer, &bufferLen) == ERROR_SUCCESS);
	if (result)
	{
		*value = *((LPDWORD)buffer);
	}

	free(buffer);

	return result;
}

void Registry::Close()
{
	if (_hkey != NULL)
	{
		RegCloseKey(_hkey);
		_hkey = NULL;
	}
}

/*
	HKEY hKey;
LONG lRes = RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Perl", 0, KEY_READ, &hKey);
bool bExistsAndSuccess (lRes == ERROR_SUCCESS);
bool bDoesNotExistsSpecifically (lRes == ERROR_FILE_NOT_FOUND);
std::wstring strValueOfBinDir;
std::wstring strKeyDefaultValue;
GetStringRegKey(hKey, L"BinDir", strValueOfBinDir, L"bad");
GetStringRegKey(hKey, L"", strKeyDefaultValue, L"bad");

LONG GetDWORDRegKey(HKEY hKey, const std::wstring &strValueName, DWORD &nValue, DWORD nDefaultValue)
{
    nValue = nDefaultValue;
    DWORD dwBufferSize(sizeof(DWORD));
    DWORD nResult(0);
    LONG nError = ::RegQueryValueExW(hKey,
        strValueName.c_str(),
        0,
        NULL,
        reinterpret_cast<LPBYTE>(&nResult),
        &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        nValue = nResult;
    }
    return nError;
}


LONG GetBoolRegKey(HKEY hKey, const std::wstring &strValueName, bool &bValue, bool bDefaultValue)
{
    DWORD nDefValue((bDefaultValue) ? 1 : 0);
    DWORD nResult(nDefValue);
    LONG nError = GetDWORDRegKey(hKey, strValueName.c_str(), nResult, nDefValue);
    if (ERROR_SUCCESS == nError)
    {
        bValue = (nResult != 0) ? true : false;
    }
    return nError;
}


LONG GetStringRegKey(HKEY hKey, const std::wstring &strValueName, std::wstring &strValue, const std::wstring &strDefaultValue)
{
    strValue = strDefaultValue;
    WCHAR szBuffer[512];
    DWORD dwBufferSize = sizeof(szBuffer);
    ULONG nError;
    nError = RegQueryValueExW(hKey, strValueName.c_str(), 0, NULL, (LPBYTE)szBuffer, &dwBufferSize);
    if (ERROR_SUCCESS == nError)
    {
        strValue = szBuffer;
    }
    return nError;
}
*/

#endif

// serial.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "stdafx.h"

#ifdef _USE_WRITE_CONSOLE
#else
/* return value need to be free */
PSTR wchar_to_multi_byte (PCWSTR wchar)
{
	int i = WideCharToMultiByte (CP_ACP, 0, wchar, -1, NULL, 0, NULL, NULL);
	PSTR str = (PSTR) malloc (i * sizeof (char));

	BOOL error_occur;
	WideCharToMultiByte (CP_ACP, 0, wchar, -1, str, i, NULL, &error_occur);
	if (error_occur)
	{
		fprintf (stderr, "error occur in converting\n");
	}
	return str;
}
#endif /* _USE_WRITE_CONSOLE */

void print_last_error (void)
{
	LPTSTR error_string = NULL;
	DWORD error_number = GetLastError ();
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error_number,
		LANG_SYSTEM_DEFAULT,
		(LPTSTR)&error_string,
		0,
		NULL 
		);

	if (error_string == NULL)
	{
		fprintf (stderr, "Unknown error number: %d\n", error_number);
	}
	else
	{
#if defined _USE_WRITE_CONSOLE
		WriteConsole (GetStdHandle(STD_OUTPUT_HANDLE), error_string, wcslen (error_string), NULL, NULL);
#else
		PSTR str = wchar_to_multi_byte (error_string);
		printf (str);
		free (str);
#endif /* _USE_WRITE_CONSOLE */
		LocalFree( error_string );
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE sh;

	sh = CreateFile (TEXT("sdfafa"),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (sh == INVALID_HANDLE_VALUE)
	{
		print_last_error ();
	}
	else
	{
		printf ("success\n");
		CloseHandle (sh);
	}

	system ("pause");
	return 0;
}
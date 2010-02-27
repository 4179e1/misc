// serial.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include "stdafx.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SetLastError (0);

	printf ("Hello world\n");

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
		LPTSTR error_string;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			LANG_CHINESE,
			(LPTSTR)&error_string,
			0,
			NULL 
			);

		if (error_string == NULL)
		{
			fprintf (stderr, "Unknown error\n");
		}
		else
		{
			wprintf (_T("%s\n"), error_string);
			LocalFree( error_string );
		}

		system ("pause");
		exit (0);
	}
	else
	{
		printf ("success\n");
		CloseHandle (sh);
	}

	system ("pause");
	return 0;
}


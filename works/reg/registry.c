#include "reg.h"
#include "registry.h"
#include "treeview.h"
#include "listview.h"

#define MAX_KEY_LENGTH 255

/*
REG_SZ			1
REG_EXPAND_SZ	2
REG_BINARY		3
REG_DWORD		4
*/

static char *value_type[] = {
	NULL,
	"REG_SZ",
	"REG_EXPAND_SZ",
	"REG_BINARY",
	"REG_DWORD",
	NULL,
};
	

void QueryKey (HKEY hKey, Reg *reg) 
{ 
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string 
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
    DWORD    cchClassName = MAX_PATH;  // size of class string 
    DWORD    cSubKeys=0;               // number of subkeys 
    DWORD    cbMaxSubKey;              // longest subkey size 
    DWORD    cchMaxClass;              // longest class string 
    DWORD    cValues;              // number of values for key 
    DWORD    cchMaxValue;          // longest value name 
    DWORD    cbMaxValueData;       // longest value data 
    DWORD    cbSecurityDescriptor; // size of security descriptor 
	DWORD	 type;
	DWORD	 len = MAX_VALUE;
	char	 data[MAX_VALUE];
	memset (data, 0, MAX_VALUE);
	data[MAX_VALUE - 1] = '\0';
	
    FILETIME ftLastWriteTime;      // last write time 
 
    DWORD i, retCode; 
 
    TCHAR  achValue[MAX_VALUE_NAME]; 
    DWORD cchValue = MAX_VALUE_NAME; 
 
    // Get the class name and the value count. 
    retCode = RegQueryInfoKey(
        hKey,                    // key handle 
        achClass,                // buffer for class name 
        &cchClassName,           // size of class string 
        NULL,                    // reserved 
        &cSubKeys,               // number of subkeys 
        &cbMaxSubKey,            // longest subkey size 
        &cchMaxClass,            // longest class string 
        &cValues,                // number of values for this key 
        &cchMaxValue,            // longest value name 
        &cbMaxValueData,         // longest value data 
        &cbSecurityDescriptor,   // security descriptor 
        &ftLastWriteTime);       // last write time 
 
    // Enumerate the subkeys, until RegEnumKeyEx fails.
    
	if (reg->status == 0) {
 	   if (cSubKeys)
 	   {
// 	       printf( "\nNumber of subkeys: %d\n", (int) cSubKeys);

 	       for (i=0; i<cSubKeys; i++) 
 	       { 
 	           cbName = MAX_KEY_LENGTH;
 	           retCode = RegEnumKeyEx(hKey, i,
 	                    achKey, 
 	                    &cbName, 
 	                    NULL, 
 	                    NULL, 
 	                    NULL, 
 	                    &ftLastWriteTime); 
 	           if (retCode == ERROR_SUCCESS) 
 	           {
//	                printf(TEXT("(%d) %s\n"), i+1, achKey);
 	   			treestore_insert (reg, g_convert (achKey, -1, "UTF-8", "GBK", NULL, NULL, NULL));
 	           }
 	       }
 	   } 
    }
 	
    // Enumerate the key values. 

    if (cValues) 
    {
//        printf( "\nNumber of values: %d\n", (int) cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++) 
        { 
            cchValue = MAX_VALUE_NAME; 
            achValue[0] = '\0'; 
			data[0] = '\0';
			len = MAX_VALUE;
			
            retCode = RegEnumValue(hKey, i, 
                achValue, 
                &cchValue, 
                NULL, 
                &type,
				data,
                &len);
 
            if (retCode == ERROR_SUCCESS ) 
            { 
				if (type == 1 || type == 2) {
					liststore_insert (GTK_TREE_VIEW (reg->listview), g_convert (achValue, -1, "UTF-8", "GBK", NULL, NULL, NULL), value_type[type], g_convert (data, -1, "UTF-8", "GBK", NULL, NULL, NULL));
				} else if (type == 3) {
					liststore_insert (GTK_TREE_VIEW (reg->listview), g_convert (achValue, -1, "UTF-8", "GBK", NULL, NULL, NULL), value_type[type], "NOT yet complete");
				} else if (type == 4) {
					char buf[10];
					sprintf (buf, "%d", *data);
					liststore_insert (GTK_TREE_VIEW (reg->listview), g_convert (achValue, -1, "UTF-8", "GBK", NULL, NULL, NULL), value_type[type], buf);
				} else {
					printf ("NOT yet complete\n");
					liststore_insert (GTK_TREE_VIEW (reg->listview), g_convert (achValue, -1, "UTF-8", "GBK", NULL, NULL, NULL), value_type[type], "NOT yet complete");
				}
            } else {
				printf ("Error code: %d\n", (int) retCode);
			}
        }
    }

}

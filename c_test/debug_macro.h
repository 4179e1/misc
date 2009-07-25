#ifndef _DEBUG_MACRO_H
#define _DEBUG_MACRO_H

/**
 *@brief Using cli option "-DDEBUG", to enable debug
 *@brief With NO DEBUG defined, expression "DEBUG_PRINT;" equals to ";"
 */
#ifdef DEBUG
#define DEBUG_PRINT printf("File: %s, Line: %d\n", __FILE__, __LINE__)
#else 
#define DEBUG_PRINT
#endif /* DEBUG */

#endif /* _DEBUG_MACRO_H */

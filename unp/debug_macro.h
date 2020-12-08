#ifndef _DEBUG_MACRO_H
#define _DEBUG_MACRO_H

#ifndef NODEBUG
#define DEBUG_PRINT (printf("File: \"%s\", Function: %s(), Line:%d\n", __FILE__, __FUNCTION__, __LINE__))
#else
#define DEBUG_PRINT
#endif /* DEBUG */

#endif /* _DEBUG_MACRO_H */

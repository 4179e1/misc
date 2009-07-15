#ifndef _IDSL_TYPES_H
#define _IDSL_TYPES_H

typedef void* idsl_element_t;

typedef enum
{
    /** Element position undefined */
    IDSL_LOCATION_UNDEF     = 0,

    /** Element is at head position */
    /* (for _node, _list, list, queue) */
    IDSL_LOCATION_HEAD      = 1,

    /** Element is on leaf position */
    /* (for _bintree, _bstree) */
    IDSL_LOCATION_ROOT      = 1,

    /** Element is at top position */
    /* (for stack)                 */
    IDSL_LOCATION_TOP       = 1,

    /** Element is at tail position */
    /* (for _node, _list, list, queue) */
    IDSL_LOCATION_TAIL      = 2,
   
    /** Element is on root position */
    /* (for _bintree, _bstree) */
    IDSL_LOCATION_LEAF      = 2,

    /** Element is at bottom position */
    /*  (for stack) */
    IDSL_LOCATION_BOTTOM    = 2,

    /** Element is the first */
    /* (for perm) */
    IDSL_LOCATION_FIRST     = 1,

    /** Element is the last */
    /* (for perm) */
    IDSL_LOCATION_LAST      = 2,

    /** Element is on first column */
    /* (for 2darray) */
    IDSL_LOCATION_FIRST_COL = 1,

    /** Element is on last column */
    /* (for 2darray) */
    IDSL_LOCATION_LAST_COL  = 2,

    /** Element is on first row */
    /* (for 2darray) */
    IDSL_LOCATION_FIRST_ROW = 4,

    /** Element is on last row */
    /* (for 2darray) */
    IDSL_LOCATION_LAST_ROW  = 8

} idsl_location_t;

typedef enum
{
    /** Memory allocation error */
    IDSL_ERR_MEM_ALLOC = -1,

    /** For stopping a parsing function */
    IDSL_MAP_STOP = 0,

    /** For continuing a parsing function */
    IDSL_MAP_CONT = 1,

    /** To indicate an inserted value */
    IDSL_INSERTED,

    /** To indicate a founded value */
    IDSL_FOUND

} idsl_constant_t;

typedef idsl_element_t
(* idsl_alloc_func_t) (void *user_data);

typedef void
(* idsl_free_func_t) (idsl_element_t E);

typedef long int
(* idsl_compare_func_t) (const idsl_element_t E, void *value);

typedef int
(* idsl_map_func_t) (const idsl_element_t E, idsl_location_t LOCATION, void * USER_DATA);

typedef void
(* idsl_write_func_t) (const idsl_element_t E, FILE* OUTPUT_FILE, idsl_location_t LOCATION, void *USER_DATA);

typedef idsl_element_t
(* idsl_copy_func_t) (const idsl_element_t E);

typedef unsigned long int ulong;

typedef enum
{
	FALSE = 0,
	TRUE = 1
} bool;

#endif /* _IDSL_TYPES_H */

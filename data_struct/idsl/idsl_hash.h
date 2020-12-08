#ifndef _IDSL_HASH_H
#define _IDSL_HASH_H

#include "idsl_types.h"

typedef struct hash_table* idsl_hash_t;

typedef const char* (*idsl_key_func_t) (void* VALUE);

typedef ulong (*idsl_hash_func_t) (const char* KEY);

ulong idsl_hash (const char* KEY);

idsl_hash_t
idsl_hash_alloc (const char* NAME, idsl_alloc_func_t ALLOC_F, idsl_free_func_t FREE_F, idsl_key_func_t KEY_F, idsl_hash_func_t HASH_F, unsigned short INITIAL_ENTRIES_NB);

void
idsl_hash_free (idsl_hash_t H);

void
idsl_hash_flush (idsl_hash_t H);

const char*
idsl_hash_get_name (const idsl_hash_t H);

unsigned short
idsl_hash_get_entries_number (const idsl_hash_t H);

unsigned short
idsl_hash_get_lists_max_size (const idsl_hash_t H);

unsigned short
idsl_hash_get_longest_list_size (const idsl_hash_t H);

ulong
idsl_hash_get_size (const idsl_hash_t H);

double
idsl_hash_get_fill_factor (const idsl_hash_t H);


idsl_hash_t
idsl_hash_set_name (idsl_hash_t H, const char* NEW_NAME);

idsl_element_t
idsl_hash_insert (idsl_hash_t H, void* VALUE);

idsl_element_t
idsl_hash_remove (idsl_hash_t H, const char* KEY);

idsl_hash_t
idsl_hash_delete (idsl_hash_t H, const char* KEY);

idsl_hash_t
idsl_hash_modify (idsl_hash_t H, unsigned short NEW_ENTRIEs_NB, unsigned short NEW_LISTS_MAX_SIZE);

idsl_element_t
idsl_hash_search (const idsl_hash_t H, const char* KEY);

idsl_element_t
idsl_hash_map(const idsl_hash_t H, idsl_map_func_t MAP_F, void* USER_DATA);

void
idsl_hash_write (const idsl_hash_t H, idsl_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

void
idsl_hash_write_xml (const idsl_hash_t H, idsl_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

void
idsl_hash_dump (const idsl_hash_t H, idsl_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

#endif /* _IDSL_HASH_H */

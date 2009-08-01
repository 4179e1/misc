#ifndef __IDSL_NODE_H
#define __IDSL_NODE_H

#include "idsl_types.h"

typedef struct _idsl_node* _idsl_node_t;

typedef int (* _idsl_node_map_func_t) (const _idsl_node_t NODE, void* USER_DATA);

typedef void (* _idsl_node_write_func_t) (const _idsl_node_t NODE, FILE* OUTPUT_FILE, void* USER_DATA);

_idsl_node_t
_idsl_node_alloc (void);

idsl_element_t
_idsl_node_free (_idsl_node_t NODE);

_idsl_node_t
_idsl_node_get_succ (const _idsl_node_t NODE);

_idsl_node_t
_idsl_node_get_pred (const _idsl_node_t NODE);

idsl_element_t
_idsl_node_get_content (const _idsl_node_t NODE);

void
_idsl_node_set_succ (_idsl_node_t NODE, const _idsl_node_t SUCC);

void
_idsl_node_set_pred (_idsl_node_t NODE, const _idsl_node_t PRED);

void
_idsl_node_set_content (_idsl_node_t NODE, const idsl_element_t CONTENT);

void
_idsl_node_link (_idsl_node_t NODE1, _idsl_node_t NODE2);

void
_idsl_node_unlink (_idsl_node_t NODE1, _idsl_node_t NODE2);

void
_idsl_node_write (const _idsl_node_t NODE, const _idsl_node_write_func_t WRITE_F, FILE* OUTPUR_FILE, void* USER_DATA);

void
_idsl_node_write_xml (const _idsl_node_t NODE, const _idsl_node_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

void
_idsl_node_dump (const _idsl_node_t NODE, const _idsl_node_write_func_t WRITE_F, FILE* OUTPUT_FILE, void* USER_DATA);

#endif /* __IDSL_NODE_H */

/*
 * This file is part of Generic Data Structures Library (IDSL).
 * Copyright (C) 1998-2006 Nicolas Darnis <ndarnis@free.fr>
 *
 * The IDSL library is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * The IDSL library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the IDSL library; see the file COPYING.
 * If not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 * $RCSfile: main_llbintree.c,v $
 * $Revision: 1.13 $
 * $Date: 2006/03/04 16:32:05 $
 */




#include <stdio.h> 
#include <string.h>
#include <stdlib.h>


#include "_idsl_bstree.h"
void
free_string (idsl_element_t e)
{
    free (e);
}

idsl_element_t
copy_string (idsl_element_t e)
{
    return (idsl_element_t) strdup ((char*) e);
}

long int
compare_strings (idsl_element_t s1, void* s2)
{
    return strcmp ((char*) s1, (char*) s2);
}


#define N 100

static void
my_write_string (const _idsl_bstree_t tree, FILE* file, void* d)
{
    idsl_element_t e = _idsl_bstree_get_content (tree);

    if (d == NULL)
	{
	    fprintf (file, "%s", (char*) e);
	}
    else
	{
	    fprintf (file, "%s%s", (char*) e, (char*) d);
	}  
}

static void
my_write_integer (const _idsl_bstree_t tree, FILE* file, void* d)
{
    idsl_element_t e = _idsl_bstree_get_content (tree);
    long int** n = (long int**) e;

    if (d == NULL)
	{
	    fprintf (file, "%ld", (long int) *n);
	}
    else
	{
	    fprintf (file, "%ld%s", (long int) *n, (char*) d);
	}
}

int main (void)
{
    int rc;
    _idsl_bstree_t t;

    printf ("Inserting 'a' in T... ");
    t  = _idsl_bstree_alloc ((idsl_element_t) "a");
    if (t != NULL)
	{
	    printf ("OK\n");
	}

    printf ("Inserting 'b' in T... ");
    _idsl_bstree_insert (&t, compare_strings, "b", &rc);
    if (rc == 0)
	{
	    printf ("OK\n");
	}

    /* Volountary insertion of an existing element: */
    printf ("Inserting ALREADY EXISTING 'a' in T... ");
    _idsl_bstree_insert (&t, compare_strings, "a", &rc);
    if (rc == IDSL_FOUND)
	{
	    printf ("KO: a already exists in T\n");
	}

    printf ("Inserting 'c' in T... ");
    _idsl_bstree_insert (&t, compare_strings, "c", &rc);
    if (rc == 0)
	{
	    printf ("OK\n");
	}

    printf ("Inserting 'd' in T... ");
    _idsl_bstree_insert (&t, compare_strings, "d", &rc);
    if (rc == 0)
	{
	    printf ("OK\n");
	}

    printf ("Inserting 'e' in T... ");
    _idsl_bstree_insert (&t, compare_strings, "e", &rc);
    if (rc == 0)
	{
	    printf ("OK\n");
	}

    printf ("Inserting 'f' in T... ");
    _idsl_bstree_insert (&t, compare_strings, "f", &rc);
    if (rc == 0)
	{
	    printf ("OK\n");
	}

    printf ("T:\n");

    _idsl_bstree_write_xml (t, my_write_string, stdout, NULL);
    _idsl_bstree_free (t, NULL);


    exit (EXIT_SUCCESS);
}


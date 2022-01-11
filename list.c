#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct item;
struct List;

void INITIALIZE ( int max_size, struct List* p_list )
{
    memset ( p_list, 0, sizeof(struct List) );
    
    p_list -> max_size = max_size;
}

void FREE ( struct List* p_list )
{
    struct item * p_item;
    if ( p_list )
    {
        p_item = p_list -> head;
        while ( p_list -> head )
        {
            p_item = p_list-> head;
            p_list -> head = p_list -> head -> next;
            free ( p_item );
        }

        p_list -> tail = NULL;
        p_list -> size = 0;
    }
}

void ADD ( int value, struct List* p_list )
{
    struct item * p_item = NULL;
    if ( p_list )
    {
        p_item = malloc (sizeof(struct item));
        if ( !p_item )
            exit ( 5 );

        p_item -> value = value;
        p_item -> next  = NULL;

        if ( p_list -> tail )
        {
            p_list  -> tail -> next = p_item;
            p_list  -> tail = p_item;
        }
        else
        {
            p_list  -> head = p_list -> tail = p_item;
        }
        p_list -> size++;
    }
}

int  CHECK ( int value, const struct List* p_list )
{
    const struct item * p_item;
    if ( p_list )
    {
        p_item = p_list -> head;

        while ( p_item )
        {
            if ( p_item -> value == value )
                return 1;
            p_item = p_item -> next;
        }

    }

    return 0;
}

void PRINT ( const struct List* p_list )
{
    const struct item * p_item;
    char prefix = '?';
    if ( p_list )
    {
        p_item = p_list -> head;
        
        while ( p_item )
        {
            if ( p_item -> value >=  1 && p_item -> value <= 15 )
                prefix = 'L';
            else
            if ( p_item -> value >= 16 && p_item -> value <= 30 )
                prefix = 'I';
            else
            if ( p_item -> value >= 31 && p_item -> value <= 45 )
                prefix = 'N';
            else
            if ( p_item -> value >= 46 && p_item -> value <= 60 )
                prefix = 'U';
            else
            if ( p_item -> value >= 61 && p_item -> value <= 75 )
                prefix = 'X';

            printf(" %c%02d",prefix,p_item->value);
            p_item = p_item -> next;
        }

        fflush(stdout);
    }
}
#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include<stdlib.h>

struct item
{
    int value;
    struct item * next;
}; 

struct List
{
    struct item *head,
                *tail;
    int size;
    int max_size;
}; 

struct item item_t;
struct List List_t;

void INITIALIZE ( int max_size, struct List* p_list );
void FREE  ( struct List* p_list );
void ADD   ( int value, struct List* p_list );
int  CHECK ( int value, const struct List* p_list );
void PRINT ( const struct List* p_list );

#endif


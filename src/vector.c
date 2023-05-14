/**
** @file vector.c
** @brief Vector as dynamic array works with metadata header
** which is hidden in memory. In constructor is allocated memory for
** header and for array, but as result is returned pointer to array and
** header is not accessible. This has effect that output array works as
** common C array, but it has hidden mettadata array which is possible to access
** with pointer aritmetics.
** This allow clean work with arrays as in higher languages as C++.
** @author Petr Horáček
*/
#include "vector.h"

#include <stdlib.h>
#include <string.h>
 

Vector(void) *
vector_new(
    size_t type_size
    , size_t length)
{
    Vector * self = 
        malloc(sizeof(Vector) + (type_size * length));

    if(self != NULL)
       *self = (Vector){.type_size = type_size, .length=length};

    return self + 1;
}


Vector(void) *
vector_new_from_array(
    size_t type_size
    , size_t length
    , void * array)
{
    size_t byte_length = type_size * length; 

    Vector * self = 
        malloc(sizeof(Vector) + byte_length);

    if(self != NULL)
    {
        *self = (Vector){.type_size=type_size, .length=length};
        memcpy(self + 1, array, byte_length);
    }

    return self + 1;
}


Vector(void) *
vector_clone(Vector * self)
{
    if(self == NULL) 
        return NULL;

    size_t memsize = 
        sizeof(Vector) + (self->type_size * self->length);

    Vector * clone = malloc(memsize);

    if(clone != NULL)
        memcpy(clone, self, memsize);

    return self + 1;
}


Vector(void) *
vector_resize(
    Vector * self
    , size_t length)
{
    if(self == NULL)
        return NULL;

    Vector * resize = 
        realloc(self, sizeof(Vector) + (self->type_size * length));

    if(resize != NULL)
    {
        resize->length = length;
        return (resize + 1);
    }
    else
        return self + 1;
}


Vector(void) *
vector_concat(
    Vector * a
    , Vector * b)
{
    if(a->type_size != b->type_size)
        return NULL;

    Vector * self = 
        vector_new(
            a->type_size
            , a->length + b->length);

    memcpy(self+1, a+1, a->type_size*a->length);
    memcpy((char*)(self+1) + (a->type_size*a->length), b+1, b->type_size*b->length);

    return self+1;
}

void
vector_delete(Vector * self)
{
    free(self);
}




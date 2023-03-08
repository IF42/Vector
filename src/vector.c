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
    , size_t length
    , VectorDelete delete)
{
    Vector_t * self = 
        malloc(sizeof(Vector_t) + (type_size * length));

    if(self != NULL)
    {
        self->type_size = type_size;
        self->length    = length;
        self->delete    = delete;
    }

    return (self + 1);
}


Vector(void) *
vector_new_init(
    size_t type_size
    , size_t length
    , void * array
    , VectorDelete delete)
{
    size_t byte_length = type_size * length; 

    Vector_t * self = 
        malloc(sizeof(Vector_t) + byte_length);

    if(self != NULL)
    {
        self->type_size = type_size;
        self->length    = length;
        self->delete    = delete;

        memcpy(self + 1, array, byte_length);
    }

    return (self + 1);
}


Vector(void) *
vector_clone(Vector_t * self)
{
    if(self == NULL) 
        return NULL;

    size_t memsize = 
        sizeof(Vector_t) + (self->type_size * self->length);

    Vector_t * clone = malloc(memsize);

    if(clone != NULL)
        memcpy(clone, self, memsize);

    return (self + 1);
}


Vector(void) *
vector_resize(
    Vector_t * self
    , size_t length)
{
    if(self == NULL)
        return NULL;

    Vector_t * resize = 
        realloc(self, sizeof(Vector_t) + (self->type_size * length));

    if(resize != NULL)
    {
        resize->length = length;
        return (resize + 1);
    }
    else
        return (self + 1);
}


void
vector_delete(Vector_t * self)
{
    if(self != NULL)
        self->delete(self);
}




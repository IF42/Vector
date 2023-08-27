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
    size_t dtype
    , size_t length)
{
    if(length == 0 || dtype == 0)
        return NULL;

    Vector * self = 
        malloc(sizeof(Vector) + (dtype * length));

    if(self != NULL)
       *self = (Vector){.dtype=dtype, .length=length};

    return self + 1;
}


Vector(void) *
vector_new_from_array(
    size_t dtype
    , size_t length
    , void * array)
{
    if(length == 0 || dtype == 0)
        return NULL;

    size_t mem_size = dtype * length; 

    Vector * self = 
        malloc(sizeof(Vector) + mem_size);

    if(self != NULL)
    {
        *self = (Vector){.dtype=dtype, .length=length};
        memcpy(self + 1, array, mem_size);
    }

    return self + 1;
}


Vector(void) *
vector_clone(Vector * self)
{
    if(self == NULL) 
        return NULL;

    size_t mem_size = 
        sizeof(Vector) + (self->dtype * self->length);

    Vector * clone = malloc(mem_size);

    if(clone != NULL)
        memcpy(clone, self, mem_size);

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
        realloc(self, sizeof(Vector) + (self->dtype * length));

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
    if(a->dtype != b->dtype)
        return NULL;

    size_t mem_size_a = a->dtype * a->length;
    size_t mem_size_b = b->dtype * b->length;

    Vector * self = 
        vector_new(
            a->dtype
            , a->length + b->length);


    memcpy(self+1, a+1, mem_size_a);
    memcpy((self+1) + mem_size_a, b+1, mem_size_b);

    return self+1;
}


void
vector_delete(Vector * self)
{
    free(self);
}




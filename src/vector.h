/**
** @file vector.h
** @brief Vector is dynamic indexed array library for C language, which 
** works as common array.
** @author Petr Horáček
*/

#ifndef _VECTOR_H_
#define _VECTOR_H_ 


#include <stddef.h>


typedef struct Vector Vector;


/**
** @brief Metadata with information about dynamic array. 
*/
struct Vector
{
    size_t length;          /** number of elemts in array */
    size_t type_size;       /** size of every element in array in bytes */
};


/**
** @brief This macro is used only as constrast with common C arrays. 
** This is only information for programmer, that it is worked 
** with Vector type which has metadata header and not with only array.
*/
#define Vector(T) T


/**
** @brief Casting macro for accessing metadata header with 
** information about dynamic array
*/
#define VECTOR(T) ((Vector *) T-1)


/**
** @brief Default constructor for Vector structure. 
** This Constructor returns pointer to start of the common array.
*/
Vector(void) *
vector_new(
    size_t type_size
    , size_t length);


/**
** @brief Simplified Vector constructor, where is not needed to write 
** explicitly type size, with operator sizeof.
*/
#define vector(T, length)          \
    vector_new(sizeof(T), length);


/**
** @brief Constructor for Vector structure with initialization.
*/
Vector(void) *
vector_new_from_array(
    size_t type_size
    , size_t length
    , void * array);


/**
** @brief Simplified Vector constructor with initialization, where is not
** beded to write explicitly data type of output vector. This type is given by
** input array data type with init values
*/
#define vector_from_array(array)                \
    vector_new_from_array(                      \
        sizeof(*array)                          \
        , sizeof(array)/sizeof(*array)          \
        , array)


/**
** @brief Clonning of the current existing vector. If the input pointer 
** is NULL, then the output from this function will be also NULL.
*/
Vector(void) *
vector_clone(Vector * self);


/**
** @brief Resizing of the given Vector instance. If the input length is 
** lower than current vector length, then the vector will be cutten and 
** last n items will be removed.
** Be carefull when the wector contains pointers with allocated memory. 
** When the vector is shinked, then the memory must be released separately!
*/
Vector(void) *
vector_resize(
    Vector * self
    , size_t length);


/**
** @brief
*/
Vector(void) *
vector_concat(
    Vector * a
    , Vector * b);


/**
** @brief destructor which release allocated memory and 
** protets of NULL pointer memory release trial.
** If the vector contains pointers to other memory, this 
** memory must be released separatly
*/
void
vector_delete(Vector * self);


#endif



/**
** @file vector.h
** @brief Vector is dynamic indexed array library for C language, which 
** works as common array.
** @author Petr Horáček
*/

#ifndef _VECTOR_H_
#define _VECTOR_H_ 


#include <stddef.h>


typedef struct Vector_t Vector_t;


/**
** @brief Data type for Vector destructor
*/
typedef void(*VectorDelete)(Vector_t *);


/**
** @brief Casting macro for vector destructor 
*/
#define VECTOR_DELETE(T)((VectorDelete) T)


/**
** @brief Metadata with information about dynamic array. 
*/
struct Vector_t
{
    size_t length;          /** number of elemts in array */
    size_t type_size;       /** size of every element in array in bytes */
    VectorDelete delete;    /** destructor for vector */
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
#define VECTOR(T) ((Vector_t *) T-1)


/**
** @brief Default constructor for Vector structure. 
** This Constructor returns pointer to start of the common array.
*/
Vector(void) *
vector_new(
    size_t type_size
    , size_t length
    , VectorDelete delete);


/**
** @brief Simplified Vector constructor, where is not needed to write 
** explicitly type size, with operator sizeof.
*/
#define vector(T, length, delete)           \
    vector_new(sizeof(T), length, VECTOR_DELETE(delete));


/**
** @brief Constructor for Vector structure with initialization.
*/
Vector(void) *
vector_new_init(
    size_t type_size
    , size_t length
    , void * array
    , VectorDelete delete);


/**
** @brief Simplified Vector constructor with initialization, where is not
** beded to write explicitly data type of output vector. This type is given by
** input array data type with init values
*/
#define vector_init(length, array, delete)      \
    vector_new_init(                            \
        sizeof(*array)                          \
        , length                                \
        , array                                 \
        , VECTOR_DELETE(delete))


/**
** @brief Clonning of the current existing vector. If the input pointer 
** is NULL, then the output from this function will be also NULL.
*/
Vector(void) *
vector_clone(Vector_t * self);


/**
** @brief Resizing of the given Vector instance. If the input length is 
** lower than current vector length, then the vector will be cutten and 
** last n items will be removed.
** Be carefull when the wector contains pointers with allocated memory. 
** When the vector is shinked, then the memory must be released separately!
*/
Vector(void) *
vector_resize(
    Vector_t * self
    , size_t length);


/**
** @brief destructor which release allocated memory and 
** protets of NULL pointer memory release trial.
** If the vector contains pointers to other memory, this 
** memory must be released separatly
*/
void
vector_delete(Vector_t * self);


#endif



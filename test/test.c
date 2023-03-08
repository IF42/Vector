#include <stdio.h>
#include <stdlib.h>

#include "../src/vector.h"


int 
main(void)
{
    Vector(float) * vec = 
        vector_init(
                10
                , ((float[10]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
                , free);    

    printf("Vector(float) {type_size = %lld, length = %lld, ["
            , VECTOR(vec)->type_size
            , VECTOR(vec)->length);

    for(size_t i = 0; i < VECTOR(vec)->length; i++)
        printf((i == 0 ? "%f" :", %f"), vec[i]);

    printf("]}\n");

    vec = vector_resize(VECTOR(vec), 5);

    printf("%lld\n", VECTOR(vec)->length);
    vector_delete(VECTOR(vec));

    printf("Program exit..");

    return EXIT_SUCCESS;
}




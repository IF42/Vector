#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../src/vector.h"


int 
main(void)
{
    Vector(float) * vec = 
        vector_from_array(
                ((float[10]) {1, 2, 3, 4, 5, 6, 7, 8, 9, 10})
                , free);    

    printf("Vector(float) {type_size = %ld, length = %ld, ["
            , VECTOR(vec)->type_size
            , VECTOR(vec)->length);

    for(size_t i = 0; i < VECTOR(vec)->length; i++)
        printf((i == 0 ? "%f" :", %f"), vec[i]);

    printf("]}\n");

    vec = vector_resize(VECTOR(vec), 5);

    printf("%ld\n", VECTOR(vec)->length);
    vector_delete(VECTOR(vec));

    printf("Program exit..");

    return EXIT_SUCCESS;
}


#if 0
int
main__(void)
{
    Vector(float) * inputs = vector_init(4, ((float[]){1, 2, 3, 2.5}), free);
    Vector(float) * weights = vector_init(12, ((float[][4]){{0.2, 0.8, -0.5, 1.0}
                                                            , {0.5, -0.91, 0.26, -0.5}
                                                            , {-0.26, -0.27, 0.17, 0.87}}), free);
    
    Vector(float) * biases = vector_init(3, ((float[]){2, 3, 0.5}), free);
    Vector(float) * output = vector(float, 3, free);

    for(size_t i = 0; i < VECTOR(output)->length; i++)
    {
        output[i] = biases[i];

        for(size_t j = 0; j < VECTOR(inputs)->length; j++)
            output[i] += ((float (*)[4]) weights)[i][j] * inputs[j];
    }


    printf("Output {");
    for(size_t i = 0; i < VECTOR(output)->length; i++)
        printf(i == 0 ? "%f": ", %f", output[i]);
    printf("}\n"); 


    vector_delete(VECTOR(weights));
    vector_delete(VECTOR(inputs));
    vector_delete(VECTOR(biases));
    vector_delete(VECTOR(output));

    return EXIT_SUCCESS;
}

Vector(void) *
vector_map(
    Vector * self
    , bool (*f)(void *))
{
    Vector(void) * vec = 
        vector(
            VECTOR(self)->type_size
            , VECTOR(self)->length
            , VECTOR(self)->delete);
    size_t matched     = 0;

    for(size_t i = 0; i < VECTOR(self)->length; i++)
    {
        if(f(&self[VECTOR(self)->type_size * i]) == true)
        {
            memcpy(
                &vec[VECTOR(vec)->type_size * matched]
                , &self[VECTOR(self)->type_size*i]
                , VECTOR(self)->type_size);
            matched++;
        }
    }   

    if(matched == 0)
    {
        vector_delete(vec);
        return NULL;
    }
    else
        return vector_resize(VECTOR(vec), matched);
}



int 
main_(void)
{
    float inputs[] = {1, 2, 3, 2.5};
    float weights[][4] = {{0.2, 0.8, -0.5, 1.0}
                         , {0.5, -0.91, 0.26, -0.5}
                         , {-0.26, -0.27, 0.17, 0.87}};
    float biases[] = {2, 3, 0.5};
    float outputs[3];

    for(size_t i = 0; i < sizeof(biases)/sizeof(float); i++)
    {
        outputs[i] = biases[i];

        for(size_t j = 0; j < sizeof(inputs)/sizeof(float); j++)
            outputs[i] += ((float (*)[4]) weights)[i][j] * inputs[j];
    }

    printf("Output {");
    for(size_t i = 0; i < sizeof(outputs)/sizeof(float); i++)
        printf(i == 0 ? "%f": ", %f", outputs[i]);
    printf("}\n"); 



    return EXIT_SUCCESS;
}
#endif

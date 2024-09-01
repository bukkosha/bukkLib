

#include "../include/Vector.h"

#include <stddef.h>
#include <stdlib.h>

typedef enum { UNINITIALIZED, INTEGER, FLOAT, DOUBLE, STRING } types;
typedef char ALIGN[16];

struct vector {
    struct {
        types dataType;
        size_t size;
        size_t capacity;
    } data;
    void *array;
};

Vector *vector_init_int(size_t initial_capacity) {
    if (initial_capacity < 1)
        return NULL;
    
    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;

    vector->data.dataType = UNINITIALIZED;
    vector->data.size = 0;
    vector->data.capacity = initial_capacity;
    vector->array = NULL;

    vector->array = malloc(initial_capacity * sizeof(int));
    if (vector->array == NULL) {
        vector_free(vector);
        return NULL;
    }
    vector->data.dataType = INTEGER;

    return vector;
}

Vector *vector_init_float(size_t initial_capacity) {
    if (initial_capacity < 1)
        return NULL;
    
    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;

    vector->data.dataType = UNINITIALIZED;
    vector->data.size = 0;
    vector->data.capacity = initial_capacity;
    vector->array = NULL;

    vector->array = malloc(initial_capacity * sizeof(float));
    if (vector->array == NULL) {
        vector_free(vector);
        return NULL;
    }
    vector->data.dataType = FLOAT;

    return vector;
}

Vector *vector_init_double(size_t initial_capacity) {
    if (initial_capacity < 1)
        return NULL;
    
    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;

    vector->data.dataType = UNINITIALIZED;
    vector->data.size = 0;
    vector->data.capacity = initial_capacity;
    vector->array = NULL;

    vector->array = malloc(initial_capacity * sizeof(DOUBLE));
    if (vector->array == NULL) {
        vector_free(vector);
        return NULL;
    }
    vector->data.dataType = DOUBLE;

    return vector;
}

Vector *vector_init_string(size_t initial_capacity) {
    if (initial_capacity < 1)
        return NULL;
    
    Vector *vector = malloc(sizeof(Vector));
    if (vector == NULL)
        return NULL;

    vector->data.dataType = UNINITIALIZED;
    vector->data.size = 0;
    vector->data.capacity = initial_capacity;
    vector->array = NULL;

    vector->array = malloc(initial_capacity * sizeof(char) + 1);
    if (vector->array == NULL) {
        vector_free(vector);
        return NULL;
    }
    vector->data.dataType = STRING;

    *(char *)vector->array = '\0';
    return vector;
}

void vector_free(Vector *vector) {
    if (vector->data.dataType == UNINITIALIZED) {
        free(vector);
        return;
    }
    free(vector->array);
    free(vector);
}

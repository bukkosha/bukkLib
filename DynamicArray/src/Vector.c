

#include "../include/Vector.h"

#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { UNINITIALIZED, INTEGER, FLOAT, DOUBLE, STRING } types;
typedef char ALIGN[16];

struct vector {
    struct {
        types dataType;
        size_t size;
        size_t capacity;
    } data;
    void* array;
};

Vector* createVector(size_t initial_capacity) {
    if (initial_capacity < 1) return NULL;
    Vector* new_vector = malloc(sizeof(Vector));
    if (!new_vector) return NULL;

    new_vector->data.dataType = UNINITIALIZED;
    new_vector->data.size = 0;
    new_vector->data.capacity = initial_capacity;
    new_vector->array = NULL;

    return new_vector;
}

void copyVector(Vector* vector, Vector* newVector) {
    if (!vector || !newVector) return;

    if (newVector->data.capacity < vector->data.capacity) return;

    switch (vector->data.dataType) {
        case INTEGER:
            newVector->array = malloc(newVector->data.capacity * sizeof(int));
            newVector->data.dataType = INTEGER;
            memcpy(
                newVector->array, vector->array,
                vector->data.size * sizeof(int));
            break;
        case FLOAT:
            newVector->array = malloc(newVector->data.capacity * sizeof(float));
            newVector->data.dataType = FLOAT;
            memcpy(
                newVector->array, vector->array,
                vector->data.size * sizeof(float));
            break;
        case DOUBLE:
            newVector->array =
                malloc(newVector->data.capacity * sizeof(double));
            newVector->data.dataType = DOUBLE;
            memcpy(
                newVector->array, vector->array,
                vector->data.size * sizeof(double));
            break;
        case STRING:
            newVector->array = malloc(newVector->data.capacity * sizeof(char));
            newVector->data.dataType = STRING;
            memcpy(
                newVector->array, vector->array,
                vector->data.size * sizeof(char));
            break;
        default:
            return;
    }
    newVector->data.size = vector->data.size;
}

void appendToVector_int(Vector* vector, void* data) {
    if (!vector || !data) return;

    if (vector->data.dataType == UNINITIALIZED) {
        vector->array = malloc(vector->data.capacity * sizeof(int));
        if (!vector->array) {
            freeVector(vector);
            return;
        }
        vector->data.dataType = INTEGER;
    }

    if (vector->data.size == vector->data.capacity) {
        Vector* newVector = createVector(vector->data.capacity * 2);
        // Make vector = newVector
    }
    ((int*)vector->array)[vector->data.size] = *(int*)data;
    vector->data.size++;
}

void appendToVector_float(Vector* vector, void* data) {
    if (!vector || !data) return;

    if (vector->data.dataType == UNINITIALIZED) {
        vector->array = malloc(vector->data.capacity * sizeof(float));
        if (!vector->array) {
            freeVector(vector);
            return;
        }
        vector->data.dataType = FLOAT;
    }
    if (vector->data.size == vector->data.capacity) {
        Vector* newVector = createVector(vector->data.capacity * 2);
        copyVector(vector, newVector);
        freeVector(vector);
        vector = newVector;
    }
    *((float*)vector->array + vector->data.size) = *(float*)data;
    vector->data.size++;
}

void appendToVector_double(Vector* vector, void* data) {
    if (!vector || !data) return;

    if (vector->data.dataType == UNINITIALIZED) {
        vector->array = malloc(vector->data.capacity * sizeof(double));
        if (!vector->array) {
            freeVector(vector);
            return;
        }
        vector->data.dataType = DOUBLE;
    }
    if (vector->data.size == vector->data.capacity) {
        Vector* newVector = createVector(vector->data.capacity * 2);
        copyVector(vector, newVector);
        freeVector(vector);
        vector = newVector;
    }
    *((double*)vector->array + vector->data.size) = *(double*)data;
    vector->data.size++;
}

void appendToVector_string(Vector* vector, void* data) {
    if (!vector || !data) return;

    if (vector->data.dataType == UNINITIALIZED) {
        vector->array = malloc(vector->data.capacity * sizeof(char));
        if (!vector->array) {
            freeVector(vector);
            return;
        }
        vector->data.dataType = STRING;
    }
    if (vector->data.size == vector->data.capacity) {
        Vector* newVector = createVector(vector->data.capacity * 2);
        copyVector(vector, newVector);
        freeVector(vector);
        vector = newVector;
    }
    *((char*)vector->array + vector->data.size) = *(char*)data;
    vector->data.size++;
}

void printVector(Vector* vector) {
    if (!vector || !vector->array) return;
    int count = 0;

    printf("{ ");
    for (int i = 0; i < vector->data.size; i++) {
        if (count) printf(", ");
        count |= 1;
        switch (vector->data.dataType) {
            case INTEGER:
                printf("%i", ((int*)vector->array)[i]);
                break;
            case FLOAT:
                printf("%f", ((float*)vector->array)[i]);
                break;
            case DOUBLE:
                printf("%lf", ((double*)vector->array)[i]);
                break;
            case STRING:
                printf("%s", ((char*)vector->array));
                break;
            default:
                printf("NULL");
                return;
        }
    }
    printf(" }\n");
}

void freeVector(Vector* vector) {
    if (vector->data.dataType == UNINITIALIZED) {
        free(vector);
        return;
    }
    free(vector->array);
    free(vector);
}



#include "../include/Vector.h"

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

    if (vector->data.size >= vector->data.capacity) {
        size_t new_capacity = vector->data.capacity * 2;
        void *new_array = (int *)realloc(vector->array, new_capacity * sizeof(int));
        if (!new_array) {
            freeVector(vector);
            return;
        }
        vector->data.capacity = new_capacity;
        vector->array = new_array;
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
    if (vector->data.size >= vector->data.capacity) {
        size_t new_capacity = vector->data.capacity * 2;
        void *new_array = (float *)realloc(vector->array, new_capacity * sizeof(float));
        if (!new_array) {
            freeVector(vector);
            return;
        }
        vector->data.capacity = new_capacity;
        vector->array = new_array;
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
    if (vector->data.size >= vector->data.capacity) {
        size_t new_capacity = vector->data.capacity * 2;
        void *new_array = (double *)realloc(vector->array, new_capacity * sizeof(double));
        if (!new_array) {
            freeVector(vector);
            return;
        }
        vector->data.capacity = new_capacity;
        vector->array = new_array;
    }
    *((double*)vector->array + vector->data.size) = *(double*)data;
    vector->data.size++;
}

void appendToVector_string(Vector* vector, void* data) {
    if (!vector || !data) return;

    if(vector->data.dataType == UNINITIALIZED) {
        vector->array = malloc(vector->data.capacity * sizeof(char));
        if (!vector->array) {
            freeVector(vector);
            return;
        }
        vector->data.dataType = STRING;
    }
    for (int i = 0; i < strlen((char*)data); i++) {
        // if copacity ends
        if (vector->data.size >= vector->data.capacity) {
            size_t new_capacity = vector->data.capacity * 2;
            void *new_array = (char *)realloc(vector->array, new_capacity * sizeof(char));
            if (!new_array) {
                freeVector(vector);
                return;
            }
            vector->data.capacity = new_capacity;
            vector->array = new_array;
        }
        // if last char is \0 change it to space
        if (*((char*)vector->array + vector->data.size) == '\0') {
            *((char*)vector->array + vector->data.size) = ' ';
            vector->data.size++;
        }
        // add char to array
        *((char*)vector->array + vector->data.size) = *((char*)data + i);
        vector->data.size++;
    }
    if (((char*)vector->array)[vector->data.size] != '\0') {
        if (vector->data.size >= vector->data.capacity) {
            size_t new_capacity = vector->data.capacity * 2;
            void *new_array = (char *)realloc(vector->array, new_capacity * sizeof(char));
            if (!new_array) {
                freeVector(vector);
                return;
            }
            vector->data.capacity = new_capacity;
            vector->array = new_array;
        }
        // add \0 to end
        *((char*)vector->array + vector->data.size) = '\0';
        vector->data.size++;
    }
}

void *vectorGetItem(Vector *vector, size_t index) {
    if (!vector || vector->data.dataType == UNINITIALIZED || index >= vector->data.size || index < 0) {
        printf("Wrong vector or index!\n");
        return NULL;
    }

    return (vector->array + (index * sizeof(int)));
}

void setVectorItem_int(Vector *vector, size_t index, void *data) {
    if (!vector) return;

    if (vector->data.dataType == UNINITIALIZED && index == 0)
        appendToVector(vector, *(int*)data);

    else if (vector->data.dataType == UNINITIALIZED && index != 0) return;

    ((int*)vector->array)[index] = *(int*)data;
}

void setVectorItem_float(Vector *vector, size_t index, void *data) {
    if (!vector) return;

    if (vector->data.dataType == UNINITIALIZED && index == 0)
        appendToVector(vector, *(float*)data);

    else if (vector->data.dataType == UNINITIALIZED && index != 0) return;

    ((float*)vector->array)[index] = *(float*)data;
}

void setVectorItem_double(Vector *vector, size_t index, void *data) {
    if (!vector) return;

    if (vector->data.dataType == UNINITIALIZED && index == 0)
        appendToVector(vector, *(double*)data);

    else if (vector->data.dataType == UNINITIALIZED && index != 0) return;

    ((double*)vector->array)[index] = *(double*)data;
}

void setVectorItem_string(Vector *vector, size_t index, void *data) {
    if (!vector) return;

    if (vector->data.dataType == UNINITIALIZED && index == 0)
        appendToVector(vector, *(char*)data);

    else if (vector->data.dataType == UNINITIALIZED && index != 0) return;

    for (int i = 0; i < strlen((char*)data); i++) {
        // if copacity ends
        if (vector->data.size >= vector->data.capacity) {
            size_t new_capacity = vector->data.capacity * 2;
            void *new_array = (char *)realloc(vector->array, new_capacity * sizeof(char));
            if (!new_array) {
                freeVector(vector);
                return;
            }
            vector->data.capacity = new_capacity;
            vector->array = new_array;
        }
        // add char to array
        *((char*)vector->array + (index + i)) = *((char*)data + i);
        if ((index + i) > vector->data.size) vector->data.size++;
    }
    if (((char*)vector->array)[vector->data.size] != '\0') {
        if (vector->data.size >= vector->data.capacity) {
            size_t new_capacity = vector->data.capacity * 2;
            void *new_array = (char *)realloc(vector->array, new_capacity * sizeof(char));
            if (!new_array) {
                freeVector(vector);
                return;
            }
            vector->data.capacity = new_capacity;
            vector->array = new_array;
        }
        // add \0 to end
        *((char*)vector->array + vector->data.size) = '\0';
        vector->data.size++;
    }
}

size_t getVectorSize(Vector *vector) { return vector->data.size; }

size_t getVectorCapacity(Vector *vector) { return vector->data.capacity; }

void popVectorBack(Vector *vector) {
    if (!vector || vector->data.dataType == UNINITIALIZED || vector->data.size < 1) return;

    switch(vector->data.dataType) {
        case INTEGER:
            ((int*)vector->array)[vector->data.size - 1] = 0;
            break;
        case FLOAT:
            ((float*)vector->array)[vector->data.size - 1] = 0;
            break;
        case DOUBLE:
            ((double*)vector->array)[vector->data.size - 1] = 0;
            break;
        case STRING:
            ((char*)vector->array)[vector->data.size - 1] = '\0';
            break;
        default:
            return;
    }
    vector->data.size--;
}

void shrinkToFitVector(Vector *vector) {
    if (vector->data.capacity < vector->data.size || vector->data.capacity == vector->data.size) return;

    void *newArray;
    switch(vector->data.dataType) {
        case INTEGER:
            newArray = (int *)realloc(vector->array, vector->data.size * sizeof(int));
            if (!newArray) return;
            break;
        case FLOAT:
            newArray = (float *)realloc(vector->array, vector->data.size * sizeof(float));
            if (!newArray) return;
            break;
        case DOUBLE:
            newArray = (double *)realloc(vector->array, vector->data.size * sizeof(double));
            if (!newArray) return;
            break;
        case STRING:
            newArray = (char *)realloc(vector->array, vector->data.size * sizeof(char));
            if (!newArray) return;
            break;
        default:
            return;
    }
    vector->data.capacity = vector->data.size;
    vector->array = newArray;
}

void resizeVector(Vector *vector, size_t newSize) {
    if (!vector || newSize < 0 || newSize == vector->data.size) return;

    if (vector->data.size > newSize) {
        vector->data.size = newSize;
        shrinkToFitVector(vector);
        return;
    }

    if (vector->data.size < newSize) {
        int diff = newSize - vector->data.size;
        int zero = 0;
        for (int i = 0; i < diff; i++) {
            appendToVector(vector, zero);
        }
    }
}

void reserveVector(Vector *vector, size_t newCapacity) {
    if (!vector || newCapacity <= vector->data.capacity) return;

    void *newArray;
    switch(vector->data.dataType) {
        case INTEGER:
            newArray = (int *)realloc(vector->array, newCapacity * sizeof(int));
            if (!newArray) return;
            break;

        case FLOAT:
            newArray = (float *)realloc(vector->array, newCapacity * sizeof(float));
            if (!newArray) return;
            break;
        case DOUBLE:
            newArray = (double *)realloc(vector->array, newCapacity * sizeof(double));
            if (!newArray) return;
            break;
        case STRING:
            newArray = (char *)realloc(vector->array, newCapacity * sizeof(char));
            if (!newArray) return;
            break;
        default:
            return;
    }
    vector->data.capacity = newCapacity;
    vector->array = newArray;
}

void printVector(Vector* vector) {
    if (!vector || !vector->array) return;
    int count = 0;

    printf("{ ");
    for (int i = 0; i < vector->data.size; i++) {
        if (vector->data.dataType == STRING) {
            i = vector->data.size;
        }
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

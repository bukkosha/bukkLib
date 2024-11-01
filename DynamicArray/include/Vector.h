#pragma once

#include <stddef.h>
#include <stdio.h>

typedef struct vector Vector;

Vector* createVector(size_t);
void copyVector(Vector*, Vector*);

void appendToVector_int(Vector*, void*);
void appendToVector_float(Vector*, void*);
void appendToVector_double(Vector*, void*);
void appendToVector_string(Vector*, void*);

#define appendToVector(X, Y)                             \
    _Generic((Y),                                        \
        int: appendToVector_int((X), ((void*)&Y)),       \
        float: appendToVector_float((X), ((void*)&Y)),   \
        double: appendToVector_double((X), ((void*)&Y)), \
        char*: appendToVector_string((X), ((void*)Y)),   \
        default: fprintf(stderr, "Unknown Type Passed To Append\n"))

void *vectorGetItem(Vector*, size_t);

void setVectorItem_int(Vector*, size_t, void*);
void setVectorItem_float(Vector*, size_t, void*);
void setVectorItem_double(Vector*, size_t, void*);
void setVectorItem_string(Vector*, size_t, void*);

#define setVectorItem(X, Y, Z)                               \
    _Generic((Z),                                            \
        int: setVectorItem_int((X), (Y), ((void*)&Z)),       \
        float: setVectorItem_float((X), (Y), ((void*)&Z)),   \
        double: setVectorItem_double((X), (Y), ((void*)&Z)), \
        char*: setVectorItem_string((X), (Y), ((void*)Z)),   \
        default: fprintf(stderr, "Unknown Type Passed To Append\n"))

size_t getVectorSize(Vector*);
size_t getVectorCapacity(Vector*);
void popVectorBack(Vector*);
void shrinkToFitVector(Vector*);
void resizeVector(Vector*, size_t);
void reserveVector(Vector*, size_t);

void printVector(Vector*);
void freeVector(Vector*);

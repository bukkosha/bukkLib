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
        /* char*: appendToVector_string((X), ((void*)Y)),  */ \
        default: fprintf(stderr, "Unknown Type Passed To Append\n"))

int getFromVector(Vector*, size_t);

void printVector(Vector*);
void freeVector(Vector*);

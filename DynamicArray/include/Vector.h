#pragma once

#include <stddef.h>

typedef struct vector Vector;

Vector *createVector(size_t initial_capacity);
void copyVector(Vector *vector, Vector *newVector);
void appendToVector_int(Vector *vector, void *data);
void appendToVector_float(Vector *vector, void *data);
void appendToVector_double(Vector *vector, void *data);
void appendToVector_string(Vector *vector, void *data);
void freeVector(Vector *vector);

#pragma once

#include <stddef.h>

typedef struct vector Vector;

Vector *createVector(size_t initial_capacity);
void freeVector(Vector *vector);

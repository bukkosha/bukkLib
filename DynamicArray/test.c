#include "include/Vector.h"

int main(void) {
    Vector* vector = createVector(3);

    for (int i = 0; i < 385; i++) {
        appendToVector(vector, i);
    }

    printVector(vector);
    freeVector(vector);
}

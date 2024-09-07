#include "include/Vector.h"

int main(void) {
    Vector* vector = createVector(3);

    for (int i = 0; i < 13; i++) {
        appendToVector(vector, i);
    }

    printf("\n\n\n%i\n\n\n", getFromVector(vector, 1));

    printVector(vector);
    freeVector(vector);
}

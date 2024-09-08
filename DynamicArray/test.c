#include "include/Vector.h"

int main(void) {
    Vector* vector = createVector(3);

    for (int i = 0; i < 13; i++) {
        appendToVector(vector, i);
    }

    int x = *(int*)vectorGetItem(vector, 5);

    printf("\n\n\n%i\n\n\n", x);

    printVector(vector);
    freeVector(vector);
}

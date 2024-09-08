#include "include/Vector.h"

int main(void) {
    Vector* vector = createVector(3);

    for (int i = 0; i < 13; i++) {
        appendToVector(vector, i);
    }
    printf("Ceated vector for 3 elememnts and apending 13 elements inside: \n");
    printVector(vector);

    int x = *(int*)vectorGetItem(vector, 5);
    printf("Geted 5-th element form vector: %i\n", x);
    printVector(vector);

    int d = 12;
    setVectorItem(vector, 5, d);
    printf("Seted 5-th element to 12:\n");
    printVector(vector);

    printf("Vector size = %zu\n", getVectorSize(vector));
    printf("Vector capacity = %zu\n", getVectorCapacity(vector));

    popVectorBack(vector);
    printf("Poping back of vector:\n");
    printVector(vector);

    resizeVector(vector, 5);
    printf("Resize vector to 5 elements:\n");
    printVector(vector);

    resizeVector(vector, 12);
    printf("Resize vector to 12 elements:\n");
    printVector(vector);

    reserveVector(vector, 15);
    freeVector(vector);
}

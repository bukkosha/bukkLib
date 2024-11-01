#include "include/Vector.h"

int main(void) {
    printf("----------char---------\n");
    printf("Ceated vector for 5 elememnts and apending Hello: \n");
    Vector* vector = createVector(5);
    printf("Vector capacity = %zu\n", getVectorCapacity(vector));

    char ds[] = "Hello";
    appendToVector(vector, ds);
    printf("Vector size = %zu\n", getVectorSize(vector));
    printVector(vector);

    int x = *(int*)vectorGetItem(vector, 4);
    printf("Geted 5-th element from vector: %i\n", x);
    printVector(vector);

    char *d = "R";
    setVectorItem(vector, 5, d);
    printf("Seted 5-th element to 12:\n");
    printVector(vector);

    printf("Append second word WORLD\n");
    appendToVector(vector, "World");
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

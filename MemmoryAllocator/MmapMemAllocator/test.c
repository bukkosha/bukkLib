#include <unistd.h>

int main() {
    int *x = sbrk(sizeof(int));
    return 0;
}

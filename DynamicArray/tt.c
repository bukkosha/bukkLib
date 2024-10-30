#include <stdio.h>
#include <string.h>

int main(void) {
    char *s = "Hello";
    void *ptr = s;
    char *t = (char*)ptr;
    
    void *array;

    for(int i = 0; i < strlen(t); i++) {
        ((char*)array)[i] = ((char*)ptr)[i];
    }
    printf("%s\n", (char*)array);
}
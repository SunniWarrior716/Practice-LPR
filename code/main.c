#include <stdio.h>
#include "recipes.h"

int main(void) {
    Book *b = newBook();
    printf("Recipe book created at %p\n", (void*)b);
    freeBook(b);
    return 0;
}

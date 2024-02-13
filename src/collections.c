#include "collections.h"
#include <stdlib.h>

void *array_init(size_t size, size_t capacity) {
    void *ptr = NULL;
    size_t bytes = size * capacity + sizeof(ArrayHeader);
    ArrayHeader *ah = malloc(bytes);

    if (ah) {
        ah[0].size = size;
        ah[0].capacity = capacity;
        ah[0].length = 0;
        ptr = ah + 1;
    }

    return ptr;
}

void *array_expand(void *array, size_t new_capacity) {
    ArrayHeader *previous_ah = array_header(array);
    size_t size = previous_ah->size;
    size_t length = previous_ah->length;

    size_t bytes = size * new_capacity + sizeof(ArrayHeader);
    ArrayHeader *new_ah = realloc(previous_ah, bytes);
    void *ptr = NULL;

    if (new_ah) {
        new_ah[0].size = size;
        new_ah[0].capacity = new_capacity;
        new_ah[0].length = length;
        ptr = new_ah + 1;
    }

    return ptr;
}

void array_remove(void *array, int pos) {
    (void)array;
    (void)pos;
}

void array_fast_remove(void *array, int pos) {
    (void)array;
    (void)pos;
}


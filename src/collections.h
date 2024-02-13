#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include <stddef.h>

#define ARRAY_DEFAULT_CAPACITY 16

typedef struct {
    size_t size;
    size_t capacity;
    size_t length;
} ArrayHeader;

#define array_header(a) ((ArrayHeader *)(a)-1)

#define array_cap(a) (array_header(a)->capacity)

#define array_len(a) (array_header(a)->length)

void *array_init(size_t size, size_t capacity);

#define array(T) array_init(sizeof(T), ARRAY_DEFAULT_CAPACITY)

void *array_expand(void *array, size_t new_capacity);

#define array_append(a, v)                                                     \
    do {                                                                       \
        if (array_len(a) + 1 >= array_cap(a))                                  \
            a = array_expand(a, array_cap(a) << 1);                            \
        (a)[array_len(a)] = (v);                                               \
        array_header(a)->length++;                                             \
    } while (0)

// TODO: implement
#define array_insert(a, v, p)                                                  \
    do {                                                                       \
        if (array_len(a) + 1 >= array_cap(a))                                  \
            a = array_expand(a, array_cap(a) << 1);                            \
        memmove();                                                             \
        (a)[(p)] = (v);                                                        \
        array_header(a)->length++;                                             \
    } while (0)

void array_remove(void *array, int pos);

void array_fast_remove(void *array, int pos);

#define array_clear(a) (array_header(a)->length = 0)

#endif // !COLLECTIONS_H

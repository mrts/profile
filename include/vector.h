#ifndef VECTOR_H__
#define VECTOR_H__

#include <stddef.h>

/**
 * A simplistic vector type that resembles std::vector from C++.
 * Takes ownership of the elements added with vector_push_back().
 */

struct vector
{
    size_t capacity;
    size_t size;
    void** elements;
};

struct vector* vector_new(size_t capacity);
/** Frees all resources, including the owned elements. */
void vector_delete(struct vector* v);

void vector_push_back(struct vector* v, void* element);
void* vector_get(struct vector* v, size_t index);

typedef void (*element_callback)(void* element);
void vector_foreach(struct vector* v, element_callback callback);

#endif /* VECTOR_H */

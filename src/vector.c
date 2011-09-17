#include "vector.h"
#include "util.h"

#include <stdlib.h>

struct vector* vector_new(size_t capacity)
{
    struct vector* v = malloc(sizeof(struct vector));
    if (!v)
        die("malloc() failed");

    v->elements = calloc(capacity, sizeof(void*));
    if (!(v->elements))
        die("calloc() failed");

    v->capacity = capacity;
    v->size = 0;

    return v;
}

void vector_push_back(struct vector* v, void* element)
{
    if (v->size == v->capacity) {

        v->capacity = v->capacity * 2;
        if (v->capacity <= v->size)
            die("Overflow error");

        v->elements = realloc(v->elements, v->capacity * sizeof(void*));
        if (!(v->elements))
            die("realloc() failed");
    }

    v->elements[v->size] = element;
    v->size++;
}

void* vector_get(struct vector* v, size_t index)
{
    if (index >= v->size)
        die("Index larger than array size");

    return v->elements[index];
}

void vector_foreach(struct vector* v, element_callback callback)
{
    int i;
    for (i = 0; i < v->size; i++)
        callback(vector_get(v, i));
}

static void delete_callback(void* element)
{
    free(element);
}

void vector_delete(struct vector* v)
{
    vector_foreach(v, delete_callback);
    free(v->elements);
    free(v);
}

#include "profile_hooks.h"
#include "util.h"

#include <stdlib.h>

// DRY
#define CREATE_SINGLETON(name)                      \
                                                    \
    struct vector* get_##name##_stats_vector()      \
    {                                               \
        static struct vector* instance = NULL;      \
                                                    \
        if (!instance) {                            \
            instance = vector_new(100);             \
            if (!instance)                          \
                die("vector_new() failed");         \
        }                                           \
                                                    \
        return instance;                            \
    }                                               \

CREATE_SINGLETON(start)
CREATE_SINGLETON(end)

static unsigned int _g_counter = 0;

void start_profile_hook(void* current_function, void* target_function)
{
    struct start_stats* stats = malloc(sizeof(struct start_stats));

    stats->current_function = (uintptr_t)current_function;
    stats->target_function = (uintptr_t)target_function;
    stats->start_time = GetTickCount();
    stats->counter = _g_counter++;

    vector_push_back(get_start_stats_vector(), stats);
}

void end_profile_hook(void* current_function)
{
    struct end_stats* stats = malloc(sizeof(struct end_stats));

    stats->current_function = (uintptr_t)current_function;
    stats->end_time = GetTickCount();
    stats->counter = _g_counter++;

    vector_push_back(get_end_stats_vector(), stats);
}

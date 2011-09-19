#ifndef PROFILE_HOOKS_H__
#define PROFILE_HOOKS_H__

#include "vector.h"

#include <stdint.h>

struct start_stats
{
    uintptr_t current_function;
    uintptr_t target_function;
    uint64_t counter;
    long start_time;
};

struct end_stats
{
    uintptr_t current_function;
    uint64_t counter;
    long end_time;
};

void start_profile_hook(void* current_function, void* target_function);
void end_profile_hook(void* current_function);

/** Singleton result accumulator access functions */
struct vector* get_start_stats_vector();
struct vector* get_end_stats_vector();

#define CALL_FUNCTION(current, target) \
    start_profile_hook(current, target); target(); end_profile_hook(target)

#endif /* PROFILE_HOOKS_H */

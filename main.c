#include "profile_hooks.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

static FILE *json_output = NULL;

static void print_start_stats_callback(void* element)
{
    struct start_stats* stats = (struct start_stats*)element;

    if (!json_output)
        die("File pointer uninitialized");

    fprintf(json_output,
            "  [%"PRIuPTR", %"PRIuPTR", %"PRIu64", %ld],\n",
            stats->current_function,
            stats->target_function,
            stats->counter,
            stats->start_time);
}

static void print_end_stats_callback(void* element)
{
    struct end_stats* stats = (struct end_stats*)element;

    if (!json_output)
        die("File pointer uninitialized");

    fprintf(json_output,
            "  [%"PRIuPTR", %"PRIu64", %ld],\n",
            stats->current_function,
            stats->counter,
            stats->end_time);
}

static void bye()
{
    json_output = fopen("profile.json", "w");
    if (!json_output)
        die("fopen(profile.json) failed");

    printf("Writing stats to file at exit...\n");

    fprintf(json_output, "{\n \"start_stats\": [\n");
    vector_foreach(get_start_stats_vector(), print_start_stats_callback);
    // remove the redundant ",\n" from the last line,
    // would break JSON parsing otherwise
    erase_last_two_chars(json_output);

    fprintf(json_output, "\n ],\n \"end_stats\": [\n");
    vector_foreach(get_end_stats_vector(), print_end_stats_callback);
    erase_last_two_chars(json_output);

    fprintf(json_output, "\n ]\n}\n");

    fclose(json_output);

    vector_delete(get_start_stats_vector());
    vector_delete(get_end_stats_vector());
}

void foo() {}

void bar() {}

int main()
{
    int i;

    if (atexit(bye) != 0)
        die("atexit() failed");

    for (i = 0; i < 1000000; i++) {
        CALL_FUNCTION(main, foo);
        CALL_FUNCTION(main, bar);
    }

    return 0;
}

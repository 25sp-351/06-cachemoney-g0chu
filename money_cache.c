#include <stdio.h>
#include <stdlib.h>
#include "money_cache.h"
#include "money_conversion.h"

#define MAX_BUFFER_SIZE 512
#define MEMO_LIMIT 150000

// Cache array for values less than MEMO_LIMIT
static char *memo[MEMO_LIMIT] = {0};

const char *money_to_text(int cents) {
    if (cents < 0)
        return "negative values not supported";

    if (cents < MEMO_LIMIT && memo[cents] != NULL)
        return memo[cents];

    char *result = (char *)malloc(MAX_BUFFER_SIZE);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    convert_money_to_text(cents, result, MAX_BUFFER_SIZE);

    if (cents < MEMO_LIMIT)
        memo[cents] = result;

    return result;
}

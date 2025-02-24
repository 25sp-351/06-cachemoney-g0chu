#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "money_conversion.h"

#define MAX_BUFFER_SIZE 512

static const char *ones[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
};

static const char *tens[] = {
    "", "", "twenty", "thirty", "forty", "fifty",
    "sixty", "seventy", "eighty", "ninety"
};

static void append_string(char *buffer, size_t *pos, size_t size, const char *str) {
    int written = snprintf(buffer + *pos, size - *pos, "%s", str);
    if (written > 0)
        *pos += (size_t)written;
}

static void append_space(char *buffer, size_t *pos, size_t size) {
    if (*pos < size - 1) {
        buffer[*pos] = ' ';
        (*pos)++;
        buffer[*pos] = '\0';
    }
}

static void convert_hundreds(int n, char *buffer, size_t *pos, size_t size) {
    if (n >= 100) {
        int hundred = n / 100;
        append_string(buffer, pos, size, ones[hundred]);
        append_space(buffer, pos, size);
        append_string(buffer, pos, size, "hundred");
        n %= 100;
        if (n > 0)
            append_space(buffer, pos, size);
    }

    if (n >= 20) {
        int ten = n / 10;
        append_string(buffer, pos, size, tens[ten]);
        if (n % 10) {
            append_string(buffer, pos, size, "-");
            append_string(buffer, pos, size, ones[n % 10]);
        }
    } else if (n > 0) {
        append_string(buffer, pos, size, ones[n]);
    } else if (*pos == 0) {
        append_string(buffer, pos, size, ones[0]);
    }
}

static void convert_number(int n, char *buffer, size_t *pos, size_t size) {
    if (n == 0) {
        append_string(buffer, pos, size, ones[0]);
        return;
    }

    if (n >= 1000000000) {
        int billions = n / 1000000000;
        convert_number(billions, buffer, pos, size);
        append_space(buffer, pos, size);
        append_string(buffer, pos, size, "billion");
        n %= 1000000000;
        if (n > 0)
            append_space(buffer, pos, size);
    }

    if (n >= 1000000) {
        int millions = n / 1000000;
        convert_number(millions, buffer, pos, size);
        append_space(buffer, pos, size);
        append_string(buffer, pos, size, "million");
        n %= 1000000;
        if (n > 0)
            append_space(buffer, pos, size);
    }

    if (n >= 1000) {
        int thousands = n / 1000;
        convert_number(thousands, buffer, pos, size);
        append_space(buffer, pos, size);
        append_string(buffer, pos, size, "thousand");
        n %= 1000;
        if (n > 0)
            append_space(buffer, pos, size);
    }

    if (n > 0)
        convert_hundreds(n, buffer, pos, size);
}

void convert_money_to_text(int cents, char *buffer, size_t size) {
    if (cents < 0) {
        snprintf(buffer, size, "negative values not supported");
        return;
    }
    
    buffer[0] = '\0';
    size_t pos = 0;
    
    int dollars = cents / 100;
    int remainder_cents = cents % 100;

    convert_number(dollars, buffer, &pos, size);
    append_space(buffer, &pos, size);
    if (dollars == 1)
        append_string(buffer, &pos, size, "dollar");
    else
        append_string(buffer, &pos, size, "dollars");

    append_space(buffer, &pos, size);
    append_string(buffer, &pos, size, "and");
    append_space(buffer, &pos, size);

    convert_number(remainder_cents, buffer, &pos, size);
    append_space(buffer, &pos, size);
    if (remainder_cents == 1)
        append_string(buffer, &pos, size, "cent");
    else
        append_string(buffer, &pos, size, "cents");
}

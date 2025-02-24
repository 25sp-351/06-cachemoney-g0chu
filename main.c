#include <stdio.h>
#include <stdlib.h>
#include "money_cache.h"

int main(void)
{
    int cents;
    while (scanf("%d", &cents) == 1) {
        const char *text = money_to_text(cents);
        printf("%s\n", text);
    }
    return 0;
}

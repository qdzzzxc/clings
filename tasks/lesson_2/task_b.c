#include <stdio.h>

int main(void)
{
    unsigned n;
    unsigned base = 2;

    if (scanf("%u", &n) != 1) {
        return 1;
    }

    unsigned start_n = n;

    while (n > 1) {
        n /= 2;
        base *= 2;
    }

    printf("%u\n", base - start_n - 1);

    return 0;
}

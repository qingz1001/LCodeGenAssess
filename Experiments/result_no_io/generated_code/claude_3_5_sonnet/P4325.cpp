#include <stdio.h>

#define MOD 42
#define MAX_INPUT 10

int main() {
    int num, i;
    int remainders[MOD] = {0};
    int distinct_count = 0;

    for (i = 0; i < MAX_INPUT; i++) {
        scanf("%d", &num);
        remainders[num % MOD] = 1;
    }

    for (i = 0; i < MOD; i++) {
        if (remainders[i] == 1) {
            distinct_count++;
        }
    }

    printf("%d\n", distinct_count);

    return 0;
}
#include <stdio.h>
#include <stdbool.h>

#define MOD 42
#define NUM_INPUTS 10

int main() {
    int numbers[NUM_INPUTS];
    bool seen[MOD] = {false};
    int distinct_count = 0;

    for (int i = 0; i < NUM_INPUTS; i++) {
        scanf("%d", &numbers[i]);
        int remainder = numbers[i] % MOD;
        if (!seen[remainder]) {
            seen[remainder] = true;
            distinct_count++;
        }
    }

    printf("%d\n", distinct_count);

    return 0;
}
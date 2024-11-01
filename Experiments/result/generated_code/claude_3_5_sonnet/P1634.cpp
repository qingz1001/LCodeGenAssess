#include <stdio.h>
#include <stdint.h>

uint64_t calculate_infected(uint64_t x, uint64_t n) {
    uint64_t total = 1;
    uint64_t new_infections = 1;

    for (uint64_t i = 0; i < n; i++) {
        new_infections *= x;
        total += new_infections;
    }

    return total;
}

int main() {
    uint64_t x, n;
    scanf("%lu %lu", &x, &n);

    uint64_t result = calculate_infected(x, n);
    printf("%lu\n", result);

    return 0;
}
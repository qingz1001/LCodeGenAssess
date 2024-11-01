#include <stdio.h>

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    int smallest_number = 0;
    int multiplier = 1;

    while (smallest_number % m != 0) {
        int digit = (smallest_number % k) + 1;
        smallest_number = smallest_number + digit * multiplier;
        multiplier *= k;
    }

    printf("%d\n", smallest_number);

    return 0;
}
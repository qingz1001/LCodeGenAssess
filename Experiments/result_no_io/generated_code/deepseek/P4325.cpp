#include <stdio.h>

int main() {
    int numbers[10];
    int remainders[42] = {0};
    int distinct_count = 0;

    for (int i = 0; i < 10; i++) {
        scanf("%d", &numbers[i]);
        int remainder = numbers[i] % 42;
        if (remainders[remainder] == 0) {
            remainders[remainder] = 1;
            distinct_count++;
        }
    }

    printf("%d\n", distinct_count);

    return 0;
}
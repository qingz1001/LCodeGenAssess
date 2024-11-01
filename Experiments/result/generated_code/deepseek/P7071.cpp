#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    if (n % 2 != 0) {
        printf("-1\n");
        return 0;
    }

    for (int i = 23; i >= 1; i--) { // 2^23 is the largest power of 2 less than 10^7
        if (n >= (1 << i)) {
            printf("%d ", 1 << i);
            n -= (1 << i);
        }
    }

    printf("\n");
    return 0;
}
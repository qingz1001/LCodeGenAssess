#include <stdio.h>

int main() {
    int k, days = 1, coins = 0;
    scanf("%d", &k);

    while (k > 0) {
        for (int i = 0; i < days && k > 0; i++) {
            coins += days;
            k--;
        }
        days++;
    }

    printf("%d\n", coins);
    return 0;
}
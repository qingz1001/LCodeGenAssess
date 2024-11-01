#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);

    int total_coins = 0;
    int days = 0;
    int current_coins = 1;
    int current_days = 1;

    while (days < k) {
        int remaining_days = k - days;
        if (remaining_days >= current_days) {
            total_coins += current_coins * current_days;
            days += current_days;
        } else {
            total_coins += current_coins * remaining_days;
            days += remaining_days;
        }
        current_coins++;
        current_days++;
    }

    printf("%d\n", total_coins);

    return 0;
}
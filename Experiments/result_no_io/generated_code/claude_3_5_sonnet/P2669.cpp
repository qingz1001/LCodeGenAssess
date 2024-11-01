#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);

    int day = 1;
    int coins = 0;
    int current_coins = 1;
    int days_at_current = 0;

    while (day <= k) {
        coins += current_coins;
        days_at_current++;
        
        if (days_at_current == current_coins) {
            current_coins++;
            days_at_current = 0;
        }
        
        day++;
    }

    printf("%d\n", coins);

    return 0;
}
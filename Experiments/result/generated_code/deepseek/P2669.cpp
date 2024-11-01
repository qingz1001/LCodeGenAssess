#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);
    
    int total_coins = 0;
    int day = 0;
    int coins_per_day = 1;
    
    while (day + coins_per_day <= k) {
        total_coins += coins_per_day * coins_per_day;
        day += coins_per_day;
        coins_per_day++;
    }
    
    total_coins += (k - day) * coins_per_day;
    
    printf("%d\n", total_coins);
    
    return 0;
}
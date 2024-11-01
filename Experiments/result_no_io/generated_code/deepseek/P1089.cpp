#include <stdio.h>

int main() {
    int budget[12];
    int total_savings = 0;
    int current_money = 0;

    for (int i = 0; i < 12; i++) {
        scanf("%d", &budget[i]);
    }

    for (int i = 0; i < 12; i++) {
        current_money += 300;
        if (current_money < budget[i]) {
            printf("-%d\n", i + 1);
            return 0;
        }
        current_money -= budget[i];
        int savings = (current_money / 100) * 100;
        total_savings += savings;
        current_money -= savings;
    }

    total_savings = total_savings * 1.2 + current_money;
    printf("%d\n", total_savings);

    return 0;
}
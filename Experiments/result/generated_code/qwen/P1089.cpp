#include <stdio.h>

int main() {
    int budget[12];
    for (int i = 0; i < 12; i++) {
        scanf("%d", &budget[i]);
    }

    int money = 0;
    int savings = 0;

    for (int month = 0; month < 12; month++) {
        money += 300;
        if (money > 100) {
            int save = money - (money % 100);
            savings += save;
            money -= save;
        }
        if (money < budget[month]) {
            printf("-%d\n", month + 1);
            return 0;
        }
        money -= budget[month];
    }

    savings += money * 1.2;
    printf("%d\n", (int)savings);

    return 0;
}
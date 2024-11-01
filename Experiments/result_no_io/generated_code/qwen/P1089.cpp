#include <stdio.h>

int main() {
    int budget[12];
    for (int i = 0; i < 12; ++i) {
        scanf("%d", &budget[i]);
    }

    int money = 0;
    int savings = 0;

    for (int month = 0; month < 12; ++month) {
        money += 300;

        if (money > 100 && money >= budget[month]) {
            int save = money - budget[month];
            if (save % 100 != 0) {
                save -= save % 100;
            }
            savings += save;
            money -= save;
        } else if (money < budget[month]) {
            printf("-%d\n", month + 1);
            return 0;
        }

        money -= budget[month];
    }

    savings += savings * 0.2;
    printf("%d\n", money + savings);

    return 0;
}
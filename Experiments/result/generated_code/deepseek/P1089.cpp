#include <stdio.h>

int main() {
    int budget[12];
    int money = 0;
    int saved = 0;

    for (int i = 0; i < 12; i++) {
        scanf("%d", &budget[i]);
    }

    for (int i = 0; i < 12; i++) {
        money += 300;
        if (money < budget[i]) {
            printf("-%d\n", i + 1);
            return 0;
        }
        money -= budget[i];
        saved += (money / 100) * 100;
        money %= 100;
    }

    int total = saved * 1.2 + money;
    printf("%d\n", total);

    return 0;
}
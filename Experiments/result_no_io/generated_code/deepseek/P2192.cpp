#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int count5 = 0, count0 = 0;
    int card;

    for (int i = 0; i < n; i++) {
        scanf("%d", &card);
        if (card == 5) {
            count5++;
        } else if (card == 0) {
            count0++;
        }
    }

    if (count0 == 0) {
        printf("-1\n");
        return 0;
    }

    if (count5 < 9) {
        printf("0\n");
        return 0;
    }

    int num5 = (count5 / 9) * 9;
    for (int i = 0; i < num5; i++) {
        printf("5");
    }
    for (int i = 0; i < count0; i++) {
        printf("0");
    }
    printf("\n");

    return 0;
}
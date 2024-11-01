#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    // Calculate the total amount collected in one week
    int weekly_amount = 0;
    for (int x = 1; x <= 100; x++) {
        for (int k = 1; k <= 100; k++) {
            weekly_amount = 0;
            for (int day = 0; day < 7; day++) {
                weekly_amount += x + day * k;
            }
            if (weekly_amount * 52 == N) {
                printf("%d\n%d\n", x, k);
                return 0;
            }
        }
    }
    return 0;
}
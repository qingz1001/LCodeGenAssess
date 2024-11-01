#include <stdio.h>

int main() {
    int n, i;
    int school_time, extra_time, total_time;
    long long unhappiness = 0, daily_unhappiness = 0;

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d", &school_time, &extra_time);
        total_time = school_time + extra_time;

        daily_unhappiness += total_time - 8;
        if (daily_unhappiness < 0) {
            daily_unhappiness = 0;
        }

        unhappiness += daily_unhappiness;
    }

    printf("%lld\n", unhappiness);

    return 0;
}
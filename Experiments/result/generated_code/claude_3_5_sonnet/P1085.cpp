#include <stdio.h>

int main() {
    int school_time, extra_time;
    int max_unhappy = 0;
    int unhappy_day = 0;

    for (int day = 1; day <= 7; day++) {
        scanf("%d %d", &school_time, &extra_time);
        int total_time = school_time + extra_time;

        if (total_time > 8 && total_time > max_unhappy) {
            max_unhappy = total_time;
            unhappy_day = day;
        }
    }

    printf("%d\n", unhappy_day);

    return 0;
}
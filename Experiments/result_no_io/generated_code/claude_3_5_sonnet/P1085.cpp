#include <stdio.h>

int main() {
    int school, extra, total;
    int max_unhappy = 0;
    int unhappy_day = 0;

    for (int day = 1; day <= 7; day++) {
        scanf("%d %d", &school, &extra);
        total = school + extra;

        if (total > 8 && total > max_unhappy) {
            max_unhappy = total;
            unhappy_day = day;
        }
    }

    printf("%d\n", unhappy_day);

    return 0;
}
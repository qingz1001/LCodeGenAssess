#include <stdio.h>

int main() {
    int school[7], mom[7];
    int unhappy_day = 0, max_hours = 0;

    for (int i = 0; i < 7; i++) {
        scanf("%d %d", &school[i], &mom[i]);
        int total_hours = school[i] + mom[i];
        if (total_hours > 8 && total_hours > max_hours) {
            max_hours = total_hours;
            unhappy_day = i + 1;
        }
    }

    printf("%d\n", unhappy_day);

    return 0;
}
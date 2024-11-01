#include <stdio.h>

int main() {
    int schedule[7][2];
    int max_unhappy_day = 0;
    int max_unhappy_hours = 8;

    for (int i = 0; i < 7; i++) {
        scanf("%d %d", &schedule[i][0], &schedule[i][1]);
        int total_hours = schedule[i][0] + schedule[i][1];
        if (total_hours > max_unhappy_hours) {
            max_unhappy_hours = total_hours;
            max_unhappy_day = i + 1;
        }
    }

    if (max_unhappy_hours > 8) {
        printf("%d\n", max_unhappy_day);
    } else {
        printf("0\n");
    }

    return 0;
}
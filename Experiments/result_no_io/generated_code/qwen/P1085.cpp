#include <stdio.h>

int main() {
    int schedule[7][2];
    for (int i = 0; i < 7; i++) {
        scanf("%d %d", &schedule[i][0], &schedule[i][1]);
    }

    int max_tiredness = -1;
    int day_with_max_tiredness = 0;

    for (int i = 0; i < 7; i++) {
        int total_hours = schedule[i][0] + schedule[i][1];
        if (total_hours > 8) {
            int tiredness = total_hours - 8;
            if (tiredness > max_tiredness) {
                max_tiredness = tiredness;
                day_with_max_tiredness = i + 1;
            }
        }
    }

    printf("%d\n", day_with_max_tiredness);

    return 0;
}
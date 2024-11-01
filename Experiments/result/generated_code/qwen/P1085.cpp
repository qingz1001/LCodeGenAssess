#include <stdio.h>

int main() {
    int max_unhappy = 0;
    int unhappy_day = 0;

    for (int i = 0; i < 7; i++) {
        int school_time, mom_time;
        scanf("%d %d", &school_time, &mom_time);
        int total_time = school_time + mom_time + 3; // 加上朗诵、舞蹈和钢琴课的3小时

        if (total_time > 8) {
            if (total_time - 8 > max_unhappy) {
                max_unhappy = total_time - 8;
                unhappy_day = i + 1;
            }
        }
    }

    printf("%d\n", unhappy_day);

    return 0;
}
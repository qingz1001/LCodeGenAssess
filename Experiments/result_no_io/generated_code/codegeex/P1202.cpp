#include <stdio.h>

int main() {
    int n, i, j;
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day_of_week = 1; // 1900年1月1日是星期一
    int counts[7] = {0}; // 用于统计每个月13日是星期几的次数

    scanf("%d", &n);

    for (i = 1900; i < 1900 + n; i++) {
        for (j = 0; j < 12; j++) {
            if (j == 1 && (i % 4 == 0 && i % 100 != 0 || i % 400 == 0)) {
                days_in_month[j] = 29; // 闰年2月有29天
            } else {
                days_in_month[j] = 28; // 平年2月有28天
            }

            if (day_of_week == 13) {
                counts[(day_of_week - 1) % 7]++;
            }

            day_of_week = (day_of_week + days_in_month[j]) % 7;
        }
    }

    // 输出结果，按照周六、日、一、二、三、四、五的顺序
    printf("%d ", counts[5]); // 周六
    printf("%d ", counts[6]); // 周日
    printf("%d ", counts[0]); // 周一
    printf("%d ", counts[1]); // 周二
    printf("%d ", counts[2]); // 周三
    printf("%d ", counts[3]); // 周四
    printf("%d\n", counts[4]); // 周五

    return 0;
}
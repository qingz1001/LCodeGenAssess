#include <stdio.h>

int main() {
    int n, days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, ans[7] = {0};
    int day_of_week = 1; // 1900年1月1日是星期一，记为1

    scanf("%d", &n);

    for (int year = 1900; year < 1900 + n; year++) {
        // 判断是否是闰年
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            days[1] = 29;
        } else {
            days[1] = 28;
        }

        for (int month = 0; month < 12; month++) {
            // 计算每个月的13号是星期几
            day_of_week = (day_of_week + 12) % 7; // 13号是星期几
            ans[day_of_week]++;
        }
    }

    // 输出结果，注意顺序是周六、周日、周一、周二、周三、周四、周五
    printf("%d %d ", ans[5], ans[6]);
    for (int i = 0; i < 5; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    return 0;
}
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int count[7] = {0};
    int day = 2; // 1900年1月1日是星期一，所以1900年1月13日是星期六

    for (int year = 1900; year < 1900 + n; year++) {
        for (int month = 0; month < 12; month++) {
            count[day]++;
            day = (day + days[month]) % 7;

            if (month == 1) { // 二月
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                    day = (day + 1) % 7; // 闰年多一天
                }
            }
        }
    }

    for (int i = 0; i < 7; i++) {
        printf("%d ", count[(i + 6) % 7]); // 从周六开始输出
    }

    return 0;
}
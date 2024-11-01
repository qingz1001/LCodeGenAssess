#include <stdio.h>

int is_leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return 1;
    return 0;
}

void count_friday_the_13th(int n) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day_of_week = 1; // 1900年1月1日是星期一
    int counts[7] = {0}; // 周六, 日, 一, 二, 三, 四, 五

    for (int year = 1900; year <= 1900 + n - 1; year++) {
        for (int month = 0; month < 12; month++) {
            if (month == 1 && is_leap_year(year)) days_in_month[month]++;
            counts[(day_of_week + 12) % 7]++; // 13号是当前月的第12天
            day_of_week = (day_of_week + days_in_month[month]) % 7;
        }
    }

    printf("%d %d %d %d %d %d %d\n", counts[5], counts[6], counts[0], counts[1], counts[2], counts[3], counts[4]);
}

int main() {
    int n;
    scanf("%d", &n);
    count_friday_the_13th(n);
    return 0;
}
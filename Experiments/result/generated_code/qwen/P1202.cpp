#include <stdio.h>

int is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

void calculate_friday_the_13ths(int n) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day_of_week = 1; // 1900/1/1 是星期一
    int count[7] = {0}; // 周六, 周日, 周一, 周二, 周三, 周四, 周五

    for (int year = 1900; year <= 1900 + n - 1; year++) {
        for (int month = 0; month < 12; month++) {
            if (month == 1 && is_leap_year(year)) {
                days_in_month[month]++;
            }
            for (int day = 1; day <= days_in_month[month]; day++) {
                if (day == 13) {
                    count[(day_of_week - 1) % 7]++;
                }
                day_of_week = (day_of_week % 7) + 1;
            }
        }
    }

    printf("%d %d %d %d %d %d %d\n", count[5], count[6], count[0], count[1], count[2], count[3], count[4]);
}

int main() {
    int n;
    scanf("%d", &n);
    calculate_friday_the_13ths(n);
    return 0;
}
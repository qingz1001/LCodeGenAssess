#include <stdio.h>

int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int counts[7] = {0}; // 0: Saturday, 1: Sunday, ..., 6: Friday

int is_leap_year(int year) {
    if (year % 400 == 0) return 1;
    if (year % 100 == 0) return 0;
    if (year % 4 == 0) return 1;
    return 0;
}

void count_fridays(int n) {
    int day_of_week = 0; // 1900-01-01 is Monday, so 0 represents Saturday
    for (int year = 1900; year < 1900 + n; year++) {
        for (int month = 0; month < 12; month++) {
            int days = days_in_month[month];
            if (month == 1 && is_leap_year(year)) days = 29;
            for (int day = 1; day <= days; day++) {
                if (day == 13) {
                    counts[day_of_week]++;
                }
                day_of_week = (day_of_week + 1) % 7;
            }
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    count_fridays(n);
    for (int i = 0; i < 7; i++) {
        printf("%d", counts[i]);
        if (i < 6) printf(" ");
    }
    printf("\n");
    return 0;
}
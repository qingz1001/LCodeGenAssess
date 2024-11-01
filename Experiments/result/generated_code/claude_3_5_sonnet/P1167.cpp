#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5000

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days[month - 1];
}

long long time_to_minutes(int year, int month, int day, int hour, int minute) {
    long long total_minutes = 0;
    for (int y = 0; y < year; y++) {
        total_minutes += is_leap_year(y) ? 366 * 24 * 60 : 365 * 24 * 60;
    }
    for (int m = 1; m < month; m++) {
        total_minutes += days_in_month(year, m) * 24 * 60;
    }
    total_minutes += (day - 1) * 24 * 60;
    total_minutes += hour * 60;
    total_minutes += minute;
    return total_minutes;
}

int main() {
    int N;
    scanf("%d", &N);

    int times[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &times[i]);
    }

    int y1, m1, d1, h1, M1;
    int y2, m2, d2, h2, M2;
    scanf("%d-%d-%d-%d:%d", &y1, &m1, &d1, &h1, &M1);
    scanf("%d-%d-%d-%d:%d", &y2, &m2, &d2, &h2, &M2);

    long long start_time = time_to_minutes(y1, m1, d1, h1, M1);
    long long end_time = time_to_minutes(y2, m2, d2, h2, M2);
    long long available_time = end_time - start_time;

    qsort(times, N, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int solved = 0;
    long long used_time = 0;
    for (int i = 0; i < N; i++) {
        if (used_time + times[i] <= available_time) {
            used_time += times[i];
            solved++;
        } else {
            break;
        }
    }

    printf("%d\n", solved);

    return 0;
}
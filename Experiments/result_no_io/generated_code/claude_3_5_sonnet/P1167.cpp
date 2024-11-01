#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5000

int n;
int times[MAX_N];
int current[5], contest[5];

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year))
        return 29;
    return days[month - 1];
}

long long time_to_minutes(int year, int month, int day, int hour, int minute) {
    long long total_minutes = 0;
    for (int y = 0; y < year; y++)
        total_minutes += is_leap_year(y) ? 366LL * 24 * 60 : 365LL * 24 * 60;
    for (int m = 1; m < month; m++)
        total_minutes += days_in_month(year, m) * 24LL * 60;
    total_minutes += (day - 1) * 24LL * 60 + hour * 60LL + minute;
    return total_minutes;
}

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &times[i]);
    
    scanf("%d-%d-%d-%d:%d", &current[0], &current[1], &current[2], &current[3], &current[4]);
    scanf("%d-%d-%d-%d:%d", &contest[0], &contest[1], &contest[2], &contest[3], &contest[4]);
    
    long long available_time = time_to_minutes(contest[0], contest[1], contest[2], contest[3], contest[4]) -
                               time_to_minutes(current[0], current[1], current[2], current[3], current[4]);
    
    qsort(times, n, sizeof(int), compare);
    
    int count = 0;
    for (int i = 0; i < n && available_time >= times[i]; i++) {
        available_time -= times[i];
        count++;
    }
    
    printf("%d\n", count);
    
    return 0;
}
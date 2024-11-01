#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} DateTime;

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

long long minutesBetweenDates(DateTime start, DateTime end) {
    long long minutes = 0;

    while (start.year < end.year || start.month < end.month || start.day < end.day || start.hour < end.hour || start.minute < end.minute) {
        start.minute++;
        if (start.minute == 60) {
            start.minute = 0;
            start.hour++;
            if (start.hour == 24) {
                start.hour = 0;
                start.day++;
                if (start.day > daysInMonth(start.year, start.month)) {
                    start.day = 1;
                    start.month++;
                    if (start.month > 12) {
                        start.month = 1;
                        start.year++;
                    }
                }
            }
        }
        minutes++;
    }

    return minutes;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int maxProblems(int *times, int n, long long totalMinutes) {
    qsort(times, n, sizeof(int), compare);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (totalMinutes >= times[i]) {
            totalMinutes -= times[i];
            count++;
        } else {
            break;
        }
    }
    return count;
}

int main() {
    int N;
    scanf("%d", &N);
    int *times = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &times[i]);
    }

    DateTime start, end;
    scanf("%d-%d-%d-%d:%d", &start.year, &start.month, &start.day, &start.hour, &start.minute);
    scanf("%d-%d-%d-%d:%d", &end.year, &end.month, &end.day, &end.hour, &end.minute);

    long long totalMinutes = minutesBetweenDates(start, end);
    int result = maxProblems(times, N, totalMinutes);
    printf("%d\n", result);

    free(times);
    return 0;
}
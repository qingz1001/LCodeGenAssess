#include <stdio.h>
#include <string.h>

int isLeapYear(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return 1;
    return 0;
}

int daysInMonth(int month, int year) {
    int days[] = {31, 28 + isLeapYear(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[month - 1];
}

int timeToMinutes(const char *timeStr) {
    int year, month, day, hour, minute;
    sscanf(timeStr, "%d-%d-%d-%d:%d", &year, &month, &day, &hour, &minute);
    int totalMinutes = 0;
    for (int y = 0; y < year; ++y) {
        totalMinutes += isLeapYear(y) ? 366 : 365;
    }
    for (int m = 1; m < month; ++m) {
        totalMinutes += daysInMonth(m, year);
    }
    totalMinutes += (day - 1) * 24 * 60 + hour * 60 + minute;
    return totalMinutes;
}

int main() {
    int N;
    scanf("%d", &N);
    int times[N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &times[i]);
    }
    char currentTime[20], examTime[20];
    scanf("%s %s", currentTime, examTime);
    int currentMinutes = timeToMinutes(currentTime);
    int examMinutes = timeToMinutes(examTime);

    int maxProblems = 0;
    for (int i = 0; i < N; ++i) {
        if (currentMinutes + times[i] <= examMinutes) {
            ++maxProblems;
            currentMinutes += times[i];
        }
    }

    printf("%d\n", maxProblems);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int is_leap_year(int year) {
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) return 1;
    return 0;
}

int days_in_month(int year, int month) {
    static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && is_leap_year(year)) return 29;
    return days[month];
}

int time_to_minutes(int year, int month, int day, int hour, int minute) {
    int total_minutes = 0;
    for (int y = 0; y < year; y++) {
        total_minutes += is_leap_year(y) ? 366 : 365;
    }
    for (int m = 1; m < month; m++) {
        total_minutes += days_in_month(year, m);
    }
    total_minutes += day - 1 + hour * 24 + minute / 60;
    return total_minutes * 24 * 60 + minute;
}

int main() {
    int N;
    scanf("%d", &N);
    int* times = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &times[i]);
    }

    char current_time[20], exam_time[20];
    scanf("%s %s", current_time, exam_time);

    // Parse the dates and times
    int current_year, current_month, current_day, current_hour, current_minute;
    sscanf(current_time, "%d-%d-%d-%d:%d", &current_year, &current_month, &current_day, &current_hour, &current_minute);

    int exam_year, exam_month, exam_day, exam_hour, exam_minute;
    sscanf(exam_time, "%d-%d-%d-%d:%d", &exam_year, &exam_month, &exam_day, &exam_hour, &exam_minute);

    int current_total_minutes = time_to_minutes(current_year, current_month, current_day, current_hour, current_minute);
    int exam_total_minutes = time_to_minutes(exam_year, exam_month, exam_day, exam_hour, exam_minute);

    int max_questions = 0;
    for (int i = 0; i < N; i++) {
        if (current_total_minutes + times[i] <= exam_total_minutes) {
            max_questions++;
            current_total_minutes += times[i];
        }
    }

    printf("%d\n", max_questions);
    free(times);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

// 定义闰年检测函数
int isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

// 计算两个日期之间的天数差
int daysBetween(int yyyy1, int mm1, int dd1, int yyyy2, int mm2, int dd2) {
    int days = 0;
    int monthDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // 计算两个年份之间的天数差
    for (int year = yyyy1; year < yyyy2; year++) {
        days += isLeapYear(year) ? 366 : 365;
    }

    // 计算当前年份到第一个日期的天数差
    for (int month = 1; month < mm1; month++) {
        days -= monthDays[month];
    }
    days -= dd1;

    // 计算第二个日期到当前年份的天数差
    for (int month = 1; month < mm2; month++) {
        days += monthDays[month];
    }
    days += dd2;

    return days;
}

// 计算两个时间之间的分钟数差
int minutesBetween(int hh1, int mm1, int hh2, int mm2) {
    int minutes = 0;
    minutes += (hh2 - hh1) * 60;
    minutes += mm2 - mm1;
    return minutes;
}

int main() {
    int N;
    scanf("%d", &N);

    int* times = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &times[i]);
    }

    int yyyy1, mm1, dd1, hh1, MM1;
    scanf("%d-%d-%d-%d:%d", &yyyy1, &mm1, &dd1, &hh1, &MM1);

    int yyyy2, mm2, dd2, hh2, MM2;
    scanf("%d-%d-%d-%d:%d", &yyyy2, &mm2, &dd2, &hh2, &MM2);

    // 计算总时间差（分钟）
    int totalMinutes = 0;
    totalMinutes += daysBetween(yyyy1, mm1, dd1, yyyy2, mm2, dd2) * 24 * 60;
    totalMinutes += minutesBetween(hh1, MM1, hh2, MM2);

    // 排序题目所需时间
    qsort(times, N, sizeof(int), (int (*)(const void *, const void *))strcmp);

    int count = 0;
    for (int i = 0; i < N; i++) {
        if (totalMinutes >= times[i]) {
            count++;
            totalMinutes -= times[i];
        } else {
            break;
        }
    }

    printf("%d\n", count);
    free(times);
    return 0;
}
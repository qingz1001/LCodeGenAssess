#include <stdio.h>
#include <string.h>

// 定义每个月的天数，平年和闰年分开考虑
int monthDays[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// 判断是否是闰年
int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    return 0;
}

// 计算从0000年到给定年份的天数
int daysFrom0000(int year) {
    int days = 0;
    for (int i = 1; i < year; i++) {
        days += isLeapYear(i) ? 366 : 365;
    }
    return days;
}

// 计算给定日期距离0000年的天数
int daysFrom0000To(int year, int month, int day) {
    int leap = isLeapYear(year);
    int days = daysFrom0000(year - 1) + monthDays[leap][month] + day;
    return days;
}

// 计算时间差（分钟）
int timeDifference(int y1, int m1, int d1, int h1, int min1, int y2, int m2, int d2, int h2, int min2) {
    int days1 = daysFrom0000To(y1, m1, d1);
    int days2 = daysFrom0000To(y2, m2, d2);
    int totalMinutes1 = days1 * 24 * 60 + h1 * 60 + min1;
    int totalMinutes2 = days2 * 24 * 60 + h2 * 60 + min2;
    return totalMinutes2 - totalMinutes1;
}

int main() {
    int N;
    scanf("%d", &N);
    int times[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &times[i]);
    }

    char currentTime[20], examTime[20];
    scanf("%s", currentTime);
    scanf("%s", examTime);

    int y1, m1, d1, h1, min1;
    sscanf(currentTime, "%d-%d-%d-%d:%d", &y1, &m1, &d1, &h1, &min1);
    int y2, m2, d2, h2, min2;
    sscanf(examTime, "%d-%d-%d-%d:%d", &y2, &m2, &d2, &h2, &min2);

    int totalTime = timeDifference(y1, m1, d1, h1, min1, y2, m2, d2, h2, min2);
    int sum = 0;
    int count = 0;

    for (int i = 0; i < N; i++) {
        sum += times[i];
        if (sum <= totalTime) {
            count++;
        } else {
            break;
        }
    }

    printf("%d\n", count);
    return 0;
}
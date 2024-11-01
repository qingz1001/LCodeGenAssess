#include <stdio.h>
#include <string.h>

int main() {
    char time1[9], time2[9];
    int n, hours1, minutes1, seconds1, hours2, minutes2, seconds2;

    scanf("%s %s %d", time1, time2, &n);

    sscanf(time1, "%d:%d:%d", &hours1, &minutes1, &seconds1);
    sscanf(time2, "%d:%d:%d", &hours2, &minutes2, &seconds2);

    int total_seconds1 = hours1 * 3600 + minutes1 * 60 + seconds1;
    int total_seconds2 = hours2 * 3600 + minutes2 * 60 + seconds2;

    int time_difference = total_seconds2 - total_seconds1;

    int stolen_notebooks = time_difference * n;

    printf("%d\n", stolen_notebooks);

    return 0;
}
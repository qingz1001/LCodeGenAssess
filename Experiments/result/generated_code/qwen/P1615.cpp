#include <stdio.h>
#include <string.h>

int main() {
    char time1[9], time2[9];
    int n, hours1, minutes1, seconds1, hours2, minutes2, seconds2;
    int total_seconds1, total_seconds2, result;

    scanf("%s %s %d", time1, time2, &n);

    sscanf(time1, "%2d:%2d:%2d", &hours1, &minutes1, &seconds1);
    sscanf(time2, "%2d:%2d:%2d", &hours2, &minutes2, &seconds2);

    total_seconds1 = hours1 * 3600 + minutes1 * 60 + seconds1;
    total_seconds2 = hours2 * 3600 + minutes2 * 60 + seconds2;

    if (total_seconds1 >= total_seconds2) {
        printf("Invalid input times\n");
        return 1;
    }

    result = (total_seconds2 - total_seconds1) * n;

    printf("%d\n", result);

    return 0;
}
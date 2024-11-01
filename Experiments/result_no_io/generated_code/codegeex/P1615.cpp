#include <stdio.h>

int main() {
    int hour1, minute1, second1, hour2, minute2, second2, n;
    scanf("%d:%d:%d", &hour1, &minute1, &second1);
    scanf("%d:%d:%d", &hour2, &minute2, &second2);
    scanf("%d", &n);

    int total_seconds1 = hour1 * 3600 + minute1 * 60 + second1;
    int total_seconds2 = hour2 * 3600 + minute2 * 60 + second2;

    int time_difference = total_seconds2 - total_seconds1;
    int stolen_notebooks = time_difference * n;

    printf("%d\n", stolen_notebooks);

    return 0;
}
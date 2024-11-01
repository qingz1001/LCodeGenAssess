#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int start_minutes = a * 60 + b;
    int end_minutes = c * 60 + d;
    int total_minutes = end_minutes - start_minutes;

    int hours = total_minutes / 60;
    int minutes = total_minutes % 60;

    printf("%d %d\n", hours, minutes);

    return 0;
}
#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int hours = c - a;
    int minutes = d - b;

    if (minutes < 0) {
        minutes += 60;
        hours--;
    }

    printf("%d %d\n", hours, minutes);

    return 0;
}
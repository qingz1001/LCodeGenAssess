#include <stdio.h>

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int minutes = (c - a) * 60 + (d - b);
    int hours = minutes / 60;
    minutes %= 60;

    printf("%d %d\n", hours, minutes);

    return 0;
}
#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    int total_cost = 0;

    for (int i = 0; i < 3; i++) {
        int begin, end;
        scanf("%d%d", &begin, &end);

        int minutes = end - begin;

        if (minutes >= 3) {
            total_cost += 3 * c * minutes;
        } else if (minutes == 2) {
            total_cost += 2 * b;
        } else if (minutes == 1) {
            total_cost += a;
        }
    }

    printf("%d\n", total_cost);

    return 0;
}
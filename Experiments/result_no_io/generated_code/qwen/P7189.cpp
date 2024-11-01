#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int total_cost = 0;

    for (int i = 0; i < 3; ++i) {
        int begin, end;
        scanf("%d %d", &begin, &end);
        int duration = end - begin;
        if (duration <= 0) continue;
        if (duration == 1) {
            total_cost += a;
        } else if (duration == 2) {
            total_cost += 2 * b;
        } else {
            total_cost += 2 * b + (duration - 2) * c;
        }
    }

    printf("%d\n", total_cost);

    return 0;
}
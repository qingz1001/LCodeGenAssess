#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int begin[3], end[3];
    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &begin[i], &end[i]);
    }

    int total_cost = 0;
    for (int i = 0; i < 3; i++) {
        int duration = end[i] - begin[i];
        if (duration == 1) {
            total_cost += a;
        } else if (duration == 2) {
            total_cost += 2 * b;
        } else if (duration >= 3) {
            total_cost += c * duration;
        }
    }

    printf("%d\n", total_cost);
    return 0;
}
#include <stdio.h>

int main() {
    int n, a, b;
    int min_cost = 1000000000;

    scanf("%d", &n);

    for (int i = 0; i < 3; i++) {
        scanf("%d %d", &a, &b);
        int packages = (n + a - 1) / a;
        int cost = packages * b;
        if (cost < min_cost) {
            min_cost = cost;
        }
    }

    printf("%d\n", min_cost);

    return 0;
}
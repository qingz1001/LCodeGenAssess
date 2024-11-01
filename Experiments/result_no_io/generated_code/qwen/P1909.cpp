#include <stdio.h>
#include <limits.h>

int main() {
    int n, a1, p1, a2, p2, a3, p3;
    scanf("%d %d %d %d %d %d", &n, &a1, &p1, &a2, &p2, &a3, &p3);

    int min_cost = INT_MAX;

    // Try each type of pencil pack
    for (int i = 0; i * a1 >= n; i++) {
        if ((i * a1 - n) % a2 == 0 || (i * a1 - n) % a3 == 0) {
            int cost = i * p1 + ((i * a1 - n) / a2) * p2 + ((i * a1 - n) / a3) * p3;
            if (cost < min_cost) {
                min_cost = cost;
            }
        }
    }

    printf("%d\n", min_cost);
    return 0;
}
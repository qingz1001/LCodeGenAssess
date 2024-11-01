#include <stdio.h>

int main() {
    int n, a1, p1, a2, p2, a3, p3;
    scanf("%d", &n);
    scanf("%d %d", &a1, &p1);
    scanf("%d %d", &a2, &p2);
    scanf("%d %d", &a3, &p3);

    int cost1 = ((n - 1) / a1 + 1) * p1;
    int cost2 = ((n - 1) / a2 + 1) * p2;
    int cost3 = ((n - 1) / a3 + 1) * p3;

    int min_cost = cost1;
    if (cost2 < min_cost) min_cost = cost2;
    if (cost3 < min_cost) min_cost = cost3;

    printf("%d\n", min_cost);

    return 0;
}
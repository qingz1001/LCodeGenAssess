#include <stdio.h>
#include <stdlib.h>

int main() {
    int a, b;
    scanf("%d %d", &a, &b);

    int distance_a = abs(a);
    int distance_b = abs(b);

    int total_moves = distance_a + distance_b;

    printf("%d\n", total_moves);

    return 0;
}
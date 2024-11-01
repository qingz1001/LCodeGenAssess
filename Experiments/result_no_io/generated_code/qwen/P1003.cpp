#include <stdio.h>

int main() {
    int n, x, y;
    scanf("%d", &n);
    int a, b, g, k;
    int top_carpet = -1;

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &a, &b, &g, &k);
        if (a <= x && x <= a + g && b <= y && y <= b + k) {
            top_carpet = i + 1;
        }
    }

    printf("%d\n", top_carpet);

    return 0;
}
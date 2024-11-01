#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    struct Carpet {
        int a, b, g, k;
    } carpets[n];

    for (int i = 0; i < n; i++) {
        scanf("%d %d %d %d", &carpets[i].a, &carpets[i].b, &carpets[i].g, &carpets[i].k);
    }

    int x, y;
    scanf("%d %d", &x, &y);

    for (int i = n - 1; i >= 0; i--) {
        if (x >= carpets[i].a && x <= carpets[i].a + carpets[i].g &&
            y >= carpets[i].b && y <= carpets[i].b + carpets[i].k) {
            printf("%d\n", i + 1);
            return 0;
        }
    }

    printf("-1\n");
    return 0;
}
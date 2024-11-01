#include <stdio.h>

#define MAX_N 10001

typedef struct {
    int x1, y1, width, height;
} Carpet;

int main() {
    int n, x, y;
    scanf("%d", &n);
    Carpet carpets[MAX_N];

    for (int i = 0; i < n; ++i) {
        scanf("%d %d %d %d", &carpets[i].x1, &carpets[i].y1, &carpets[i].width, &carpets[i].height);
    }

    scanf("%d %d", &x, &y);

    int result = -1;
    for (int i = n - 1; i >= 0; --i) {
        if (x >= carpets[i].x1 && x <= carpets[i].x1 + carpets[i].width &&
            y >= carpets[i].y1 && y <= carpets[i].y1 + carpets[i].height) {
            result = i + 1;
            break;
        }
    }

    printf("%d\n", result);

    return 0;
}
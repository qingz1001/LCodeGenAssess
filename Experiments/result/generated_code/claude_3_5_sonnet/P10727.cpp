#include <stdio.h>

#define MAX_N 100

int main() {
    int n, h, w;
    int max_area = 0;
    int area;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &h, &w);
        area = h * w;
        if (area > max_area) {
            max_area = area;
        }
    }

    printf("%d\n", max_area);

    return 0;
}
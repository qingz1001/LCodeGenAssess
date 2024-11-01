#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int max_area = 0;
    int h, w, area;

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
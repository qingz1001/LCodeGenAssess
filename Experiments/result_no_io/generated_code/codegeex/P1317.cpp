#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int count = 0;
    int i = 0;
    while (i < n - 1) {
        if (heights[i] > heights[i + 1]) {
            i++;
            while (i < n - 1 && heights[i] > heights[i + 1]) {
                i++;
            }
            count++;
        }
        i++;
    }

    printf("%d\n", count);
    return 0;
}
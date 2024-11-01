#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int heights[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }

    int count = 0;
    for (int i = 1; i < n - 1; i++) {
        if (heights[i] > heights[i - 1] && heights[i] > heights[i + 1]) {
            int leftMax = heights[i - 1];
            int rightMax = heights[i + 1];
            for (int j = i - 2; j >= 0; j--) {
                if (heights[j] > leftMax) {
                    leftMax = heights[j];
                }
            }
            for (int j = i + 2; j < n; j++) {
                if (heights[j] > rightMax) {
                    rightMax = heights[j];
                }
            }
            if (leftMax > heights[i] && rightMax > heights[i]) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}
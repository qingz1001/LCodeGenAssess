#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int max_width = 0;
    int start = 0;

    while (start < N) {
        int end = start;
        while (end + 1 < N && heights[end + 1] >= heights[end]) {
            end++;
        }
        while (end + 1 < N && heights[end + 1] <= heights[end]) {
            end++;
        }
        int width = end - start + 1;
        if (width > max_width) {
            max_width = width;
        }
        start = end + 1;
    }

    printf("%d\n", max_width);
    return 0;
}
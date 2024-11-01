#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int *heights = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int max_width = 0;

    for (int i = 1; i < N - 1; i++) {
        int left = i, right = i;
        while (left > 0 && heights[left - 1] <= heights[left]) {
            left--;
        }
        while (right < N - 1 && heights[right + 1] <= heights[right]) {
            right++;
        }
        int width = right - left + 1;
        if (width > max_width) {
            max_width = width;
        }
    }

    printf("%d\n", max_width);

    free(heights);
    return 0;
}
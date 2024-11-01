#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10000

int main() {
    int N;
    scanf("%d", &N);

    int heights[MAX_N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }

    int maxWidth = 0;
    for (int i = 0; i < N; i++) {
        int left = i, right = i;
        
        // 向左扩展
        while (left > 0 && heights[left - 1] <= heights[left]) {
            left--;
        }
        
        // 向右扩展
        while (right < N - 1 && heights[right + 1] <= heights[right]) {
            right++;
        }
        
        int width = right - left + 1;
        if (width > maxWidth) {
            maxWidth = width;
        }
    }

    printf("%d\n", maxWidth);

    return 0;
}
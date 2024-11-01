#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }
    
    int max_width = 0;
    
    for (int i = 1; i < N - 1; i++) {
        int left = i - 1;
        while (left >= 0 && heights[left] <= heights[left + 1]) {
            left--;
        }
        
        int right = i + 1;
        while (right < N && heights[right] <= heights[right - 1]) {
            right++;
        }
        
        int width = right - left - 1;
        if (width > max_width) {
            max_width = width;
        }
    }
    
    printf("%d\n", max_width);
    
    return 0;
}
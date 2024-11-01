#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }
    
    int max_width = 0;
    
    for (int i = 0; i < N; i++) {
        int start = i;
        while (i + 1 < N && heights[i] <= heights[i + 1]) {
            i++;
        }
        
        while (i + 1 < N && heights[i] >= heights[i + 1]) {
            i++;
        }
        
        max_width = (i - start + 1 > max_width) ? (i - start + 1) : max_width;
    }
    
    printf("%d\n", max_width);
    
    return 0;
}
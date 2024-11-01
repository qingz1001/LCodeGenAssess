#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    
    long long heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%lld", &heights[i]);
    }
    
    int max_width = 0;
    int current_width = 1;
    
    for (int i = 1; i < N; i++) {
        if (heights[i] == heights[i - 1]) {
            current_width++;
        } else if (heights[i] > heights[i - 1]) {
            int j = i + 1;
            while (j < N && heights[j] >= heights[j - 1]) {
                j++;
            }
            current_width += j - i;
            i = j - 1;
        } else {
            int j = i + 1;
            while (j < N && heights[j] <= heights[j - 1]) {
                j++;
            }
            current_width += j - i;
            i = j - 1;
        }
        
        if (current_width > max_width) {
            max_width = current_width;
        }
        
        current_width = 1;
    }
    
    printf("%d\n", max_width);
    
    return 0;
}
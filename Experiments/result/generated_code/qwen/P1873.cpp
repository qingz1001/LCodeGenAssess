#include <stdio.h>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    int heights[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &heights[i]);
    }
    
    int left = 0, right = 400000, result = 0;
    
    while (left <= right) {
        int mid = (left + right) / 2;
        long long total = 0;
        
        for (int i = 0; i < N; i++) {
            if (heights[i] > mid) {
                total += heights[i] - mid;
            }
        }
        
        if (total >= M) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}
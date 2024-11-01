#include <stdio.h>

#define MAX_N 10000

int main() {
    int n;
    int heights[MAX_N];
    int low_lands = 0;
    int is_low = 0;
    
    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &heights[i]);
    }
    
    // 统计低洼地
    for (int i = 1; i < n - 1; i++) {
        if (heights[i] < heights[i-1] && !is_low) {
            is_low = 1;
        } else if (heights[i] > heights[i-1] && is_low) {
            low_lands++;
            is_low = 0;
        }
    }
    
    // 输出结果
    printf("%d\n", low_lands);
    
    return 0;
}
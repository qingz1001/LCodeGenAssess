#include <stdio.h>

int main() {
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);
    
    int current_pos = 0; // 初始位置在屏幕最左边
    int total_distance = 0;
    
    for (int i = 0; i < J; i++) {
        int apple_pos;
        scanf("%d", &apple_pos);
        
        if (apple_pos < current_pos) {
            // 苹果在船的左边，需要向右移动
            total_distance += current_pos - apple_pos;
            current_pos = apple_pos;
        } else if (apple_pos > current_pos + M - 1) {
            // 苹果在船的右边，需要向左移动
            total_distance += apple_pos - (current_pos + M - 1);
            current_pos = apple_pos - M + 1;
        }
    }
    
    printf("%d\n", total_distance);
    return 0;
}
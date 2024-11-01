#include <stdio.h>

int main() {
    int N, M, J;
    scanf("%d %d %d", &N, &M, &J);
    
    int current_position = 1; // 初始位置，船在最左边的M列
    int total_distance = 0; // 总移动距离
    
    for (int i = 0; i < J; i++) {
        int apple_position;
        scanf("%d", &apple_position);
        
        if (apple_position < current_position) {
            // 苹果在船的左边，需要向右移动
            total_distance += current_position - apple_position;
            current_position = apple_position;
        } else if (apple_position > current_position + M - 1) {
            // 苹果在船的右边，需要向左移动
            total_distance += apple_position - (current_position + M - 1);
            current_position = apple_position - M + 1;
        }
        // 如果苹果在船内，则不需要移动
    }
    
    printf("%d\n", total_distance);
    return 0;
}
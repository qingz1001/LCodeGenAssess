#include <stdio.h>

int main() {
    int M, S, T;
    scanf("%d %d %d", &M, &S, &T);
    
    int time = 0;
    int distance = 0;
    int max_distance = 0;
    
    while (time < T) {
        // 如果魔法值足够，使用闪烁
        if (M >= 10) {
            distance += 60;
            M -= 10;
        } else {
            // 否则跑步
            distance += 17;
        }
        
        time++;
        
        // 更新最大距离
        if (distance > max_distance) {
            max_distance = distance;
        }
        
        // 检查是否已经逃离
        if (distance >= S) {
            printf("Yes\n%d\n", time);
            return 0;
        }
        
        // 恢复魔法值
        M += 4;
        if (M > 100) {
            M = 100;
        }
    }
    
    // 如果时间用完仍未逃离
    printf("No\n%d\n", max_distance);
    return 0;
}
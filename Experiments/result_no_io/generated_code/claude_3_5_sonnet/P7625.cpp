#include <stdio.h>
#include <stdlib.h>

#define MAX_N 10
#define MAX_J 20

int main() {
    int N, M, J;
    int apples[MAX_J];
    int left = 1, right, move = 0;
    
    // 读取输入
    scanf("%d %d", &N, &M);
    scanf("%d", &J);
    for (int i = 0; i < J; i++) {
        scanf("%d", &apples[i]);
    }
    
    right = M;
    
    // 处理每个苹果
    for (int i = 0; i < J; i++) {
        if (apples[i] < left) {
            // 船需要向左移动
            move += left - apples[i];
            left = apples[i];
            right = left + M - 1;
        } else if (apples[i] > right) {
            // 船需要向右移动
            move += apples[i] - right;
            right = apples[i];
            left = right - M + 1;
        }
        // 如果苹果在船的范围内，不需要移动
    }
    
    // 输出结果
    printf("%d\n", move);
    
    return 0;
}
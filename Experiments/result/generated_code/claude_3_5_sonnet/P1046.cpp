#include <stdio.h>

#define APPLES 10

int main() {
    int heights[APPLES];
    int reach, count = 0;
    
    // 输入苹果的高度
    for (int i = 0; i < APPLES; i++) {
        scanf("%d", &heights[i]);
    }
    
    // 输入陶陶能够达到的最大高度
    scanf("%d", &reach);
    
    // 计算陶陶能摘到的苹果数量
    for (int i = 0; i < APPLES; i++) {
        if (heights[i] <= reach + 30) {
            count++;
        }
    }
    
    // 输出结果
    printf("%d\n", count);
    
    return 0;
}
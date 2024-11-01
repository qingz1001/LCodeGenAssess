#include <stdio.h>

int main() {
    int apples[10];
    int height, count = 0;
    
    // 输入10个苹果的高度
    for (int i = 0; i < 10; i++) {
        scanf("%d", &apples[i]);
    }
    
    // 输入陶陶能够达到的最大高度
    scanf("%d", &height);
    
    // 计算陶陶能摘到的苹果数量
    for (int i = 0; i < 10; i++) {
        if (apples[i] <= height + 30) {
            count++;
        }
    }
    
    // 输出结果
    printf("%d\n", count);
    
    return 0;
}
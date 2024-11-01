#include <stdio.h>

int main() {
    int numbers[8];
    int indices[8];
    
    // 读取输入的8个数字
    for (int i = 0; i < 8; i++) {
        scanf("%d", &numbers[i]);
        indices[i] = i + 1; // 记录每个数字的原始编号
    }
    
    // 对数字进行排序，同时保持编号的对应关系
    for (int i = 0; i < 8; i++) {
        for (int j = i + 1; j < 8; j++) {
            if (numbers[i] < numbers[j]) {
                // 交换数字
                int temp = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp;
                // 交换对应的编号
                temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }
    
    // 计算最大的5个数字的和
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += numbers[i];
    }
    
    // 输出最大的和
    printf("%d\n", sum);
    
    // 输出这5个数字的编号
    for (int i = 0; i < 5; i++) {
        printf("%d ", indices[i]);
    }
    
    return 0;
}
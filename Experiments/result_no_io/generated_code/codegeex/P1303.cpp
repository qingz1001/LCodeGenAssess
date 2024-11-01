#include <stdio.h>
#include <string.h>

#define MAX_SIZE 2001

int main() {
    char a[MAX_SIZE], b[MAX_SIZE];
    int c[MAX_SIZE * 2] = {0};
    
    // 读取输入的两个大整数
    scanf("%s %s", a, b);
    
    // 将字符串形式的大整数转换为整数数组形式
    int len_a = strlen(a);
    int len_b = strlen(b);
    for (int i = 0; i < len_a; i++) {
        a[i] -= '0';
    }
    for (int i = 0; i < len_b; i++) {
        b[i] -= '0';
    }
    
    // 逐位相乘并累加到结果数组中
    for (int i = len_a - 1; i >= 0; i--) {
        for (int j = len_b - 1; j >= 0; j--) {
            c[i + j + 1] += a[i] * b[j];
        }
    }
    
    // 处理进位
    for (int i = len_a + len_b; i > 0; i--) {
        if (c[i] >= 10) {
            c[i - 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    
    // 找到结果的起始位置
    int start = 0;
    while (c[start] == 0 && start < len_a + len_b - 1) {
        start++;
    }
    
    // 输出结果
    if (start == len_a + len_b - 1 && c[start] == 0) {
        printf("0\n");
    } else {
        for (int i = start; i < len_a + len_b; i++) {
            printf("%d", c[i]);
        }
        printf("\n");
    }
    
    return 0;
}
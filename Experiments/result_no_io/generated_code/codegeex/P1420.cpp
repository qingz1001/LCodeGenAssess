#include <stdio.h>

int main() {
    int n, a[10000], i, j, max, current;
    
    // 读取输入的整数n
    scanf("%d", &n);
    
    // 读取输入的n个整数
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // 初始化最大连号长度为1
    max = 1;
    
    // 遍历数组，寻找最长连号
    for (i = 0; i < n; i++) {
        current = 1; // 当前连号长度
        for (j = i + 1; j < n; j++) {
            // 如果当前数字是前一个数字加1，则连号长度加1
            if (a[j] == a[j - 1] + 1) {
                current++;
            } else {
                break; // 否则跳出内层循环
            }
        }
        // 更新最大连号长度
        if (current > max) {
            max = current;
        }
    }
    
    // 输出最长连号的长度
    printf("%d\n", max);
    
    return 0;
}
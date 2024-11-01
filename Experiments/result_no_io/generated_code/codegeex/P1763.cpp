#include <stdio.h>

int main() {
    int a, b;
    scanf("%d%d", &a, &b);

    // 枚举分母，从最大的开始，确保单位分数从小到大
    for (int i = b; i >= 1; i--) {
        // 检查当前分母是否可以整除分子
        if (a * i % b == 0) {
            // 如果可以整除，输出该分母
            printf("%d ", i);
            // 更新分子为剩余部分
            a = a * i / b;
            // 重置分母为b
            i = b;
        }
    }

    return 0;
}
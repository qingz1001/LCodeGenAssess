#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char x[101], y[101], z[101];

    // 读取输入
    scanf("%d", &n);
    scanf("%s", x);
    scanf("%s", y);

    // 初始化 z 字符串
    for (int i = 0; i < n; i++) {
        // 计算 z[i] = max(x[i], y[i])
        z[i] = (x[i] > y[i]) ? y[i] : x[i];
    }

    // 检查是否满足 f(x, z) = y
    for (int i = 0; i < n; i++) {
        if (z[i] != y[i]) {
            // 如果不满足，输出 -1
            printf("-1\n");
            return 0;
        }
    }

    // 输出找到的字符串 z
    printf("%s\n", z);

    return 0;
}
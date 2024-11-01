#include <stdio.h>

#define MAX_N 10000

int main() {
    int n, a[MAX_N];
    int maxLen = 1, currentLen = 1;

    // 读取输入
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // 计算最长连号
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i-1] + 1) {
            currentLen++;
            if (currentLen > maxLen) {
                maxLen = currentLen;
            }
        } else {
            currentLen = 1;
        }
    }

    // 输出结果
    printf("%d\n", maxLen);

    return 0;
}
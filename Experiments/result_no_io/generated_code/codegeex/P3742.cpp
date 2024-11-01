#include <stdio.h>
#include <string.h>

int main() {
    int n;
    char x[101], y[101], z[101];

    // 读取输入
    scanf("%d", &n);
    scanf("%s", x);
    scanf("%s", y);

    // 遍历字符串，计算z
    for (int i = 0; i < n; i++) {
        if (x[i] < y[i]) {
            printf("-1");
            return 0;
        } else {
            z[i] = y[i];
        }
    }

    // 输出结果
    printf("%s", z);

    return 0;
}
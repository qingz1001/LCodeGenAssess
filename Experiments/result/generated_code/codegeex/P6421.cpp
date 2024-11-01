#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int a[1001] = {0}; // 初始化数组，所有元素为0表示未被划掉
    int count = 0; // 计数器，记录被划掉的数字个数

    for (int i = 2; i <= n; i++) {
        if (a[i] == 0) { // 如果当前数字未被划掉
            for (int j = i * 2; j <= n; j += i) { // 划掉当前数字的倍数
                a[j] = 1; // 标记为已划掉
                count++;
                if (count == k) { // 如果已划掉的数字个数达到k
                    printf("%d\n", j); // 输出第k个被划掉的数字
                    return 0;
                }
            }
        }
    }

    return 0;
}
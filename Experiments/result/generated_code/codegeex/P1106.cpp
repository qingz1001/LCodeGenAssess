#include <stdio.h>
#include <string.h>

int main() {
    char n[251];
    int k, len, i, j;
    int flag = 0;

    // 读取高精度的正整数 n
    scanf("%s", n);
    // 读取需要删除的数字个数 k
    scanf("%d", &k);

    len = strlen(n);

    // 从左到右遍历数字，删除 k 个最大的数字
    for (i = 0; i < k; i++) {
        for (j = 0; j < len - 1; j++) {
            if (n[j] > n[j + 1]) {
                n[j] = n[j + 1];
                flag = 1;
            }
        }
        if (flag == 0) break; // 如果没有交换，说明已经是最小的数
        flag = 0;
    }

    // 去除前导零
    while (n[0] == '0' && len > 1) {
        for (i = 0; i < len - 1; i++) {
            n[i] = n[i + 1];
        }
        len--;
    }

    // 输出剩下的数字
    printf("%s\n", n);

    return 0;
}
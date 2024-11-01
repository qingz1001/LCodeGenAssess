#include <stdio.h>
#include <string.h>

int main() {
    char n[251];
    int k;
    scanf("%s%d", n, &k);
    int len = strlen(n);

    // 删除k个数字，使得剩下的数字最小
    for (int i = 0; i < k; i++) {
        int pos = 0;
        // 找到第一个非递增的位置
        for (int j = 1; j < len; j++) {
            if (n[j] < n[pos]) {
                pos = j;
            }
        }
        // 删除找到的位置
        for (int j = pos; j < len - 1; j++) {
            n[j] = n[j + 1];
        }
        len--;
    }

    // 去掉前导0
    int start = 0;
    while (start < len && n[start] == '0') {
        start++;
    }

    // 输出结果
    if (start == len) {
        printf("0\n");
    } else {
        for (int i = start; i < len; i++) {
            printf("%c", n[i]);
        }
        printf("\n");
    }

    return 0;
}
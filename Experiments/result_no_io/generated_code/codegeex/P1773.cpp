#include <stdio.h>
#include <string.h>

#define MAX_LEN 1001

int main() {
    char num[MAX_LEN];
    int m;
    scanf("%s %d", num, &m);
    int len = strlen(num);

    int min_x = m, min_k = 1, max_x = 0, max_k = 1;

    // 遍历所有可能的分割点
    for (int i = 0; i < len; ++i) {
        int x = num[i] - '0';
        int k = 1;
        
        // 计算当前分割点的乘积对m的余数
        for (int j = i + 1; j < len; ++j) {
            x = (x * 10 + num[j] - '0') % m;
            ++k;
        }

        // 更新最小值和最大值
        if (x < min_x) {
            min_x = x;
            min_k = k;
        }
        if (x > max_x) {
            max_x = x;
            max_k = k;
        }
    }

    printf("%d %d %d %d\n", min_x, min_k, max_x, max_k);
    return 0;
}
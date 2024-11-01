#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    while (k--) {
        int w;
        scanf("%d", &w);
        int *positions = (int *)malloc(w * sizeof(int));
        for (int i = 0; i < w; i++) {
            scanf("%d", &positions[i]);
        }

        // 初始化必胜状态为否
        int isWinning = 0;

        // 遍历所有白色格子
        for (int i = 0; i < w; i++) {
            int position = positions[i];
            int divisor = 1;

            // 找到所有能整除position的数
            while (position * divisor <= n) {
                divisor++;
            }

            // 如果有任何一个位置能整除的数多于一个，则先手必胜
            if (divisor > 1) {
                isWinning = 1;
                break;
            }
        }

        // 输出结果
        if (isWinning) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

        // 释放内存
        free(positions);
    }

    return 0;
}
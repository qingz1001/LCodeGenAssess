#include <stdio.h>

#define MAX_N 100

int main() {
    int n, i, j;
    int fish[MAX_N];
    int count[MAX_N] = {0};

    // 输入鱼的数量
    scanf("%d", &n);

    // 输入每条鱼的可爱程度
    for (i = 0; i < n; i++) {
        scanf("%d", &fish[i]);
    }

    // 计算每条鱼左边不如它可爱的鱼的数量
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) {
            if (fish[j] < fish[i]) {
                count[i]++;
            }
        }
    }

    // 输出结果
    for (i = 0; i < n; i++) {
        printf("%d", count[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");

    return 0;
}
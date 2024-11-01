#include <stdio.h>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N;
        scanf("%d", &N);

        int a[N];
        for (int i = 0; i < N; i++) {
            scanf("%d", &a[i]);
        }

        // 检查是否可以划分为两个严格递增子序列
        int count = 0;
        for (int i = 0; i < N; i++) {
            if (a[i] > a[i + 1]) {
                count++;
            }
        }

        if (count <= 1) {
            printf("Yes!\n");
        } else {
            printf("No!\n");
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    scanf("%d", &N);
    int *s = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        scanf("%d", &s[i]);
    }

    // 找到最大的余数
    int max_remainder = -1;
    for (int i = 0; i < N; i++) {
        if (s[i] > max_remainder) {
            max_remainder = s[i];
        }
    }

    // 最小的 K 至少是 max_remainder + 1
    int K = max_remainder + 1;

    free(s);
    printf("%d\n", K);

    return 0;
}
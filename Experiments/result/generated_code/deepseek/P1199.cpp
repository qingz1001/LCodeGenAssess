#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500

int N;
int默契值[MAXN][MAXN];

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            scanf("%d", &默契值[i][j]);
            默契值[j][i] = 默契值[i][j]; // 对称矩阵
        }
    }

    int max_默契值 = 0;
    for (int i = 0; i < N; i++) {
        int max_默契值_i = 0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                if (默契值[i][j] > max_默契值_i) {
                    max_默契值_i = 默契值[i][j];
                }
            }
        }
        if (max_默契值_i > max_默契值) {
            max_默契值 = max_默契值_i;
        }
    }

    printf("1\n%d\n", max_默契值);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

int main() {
    int N, M;
    int Ini[MAX_N][MAX_M], Fin[MAX_N][MAX_M];
    int i, j, k, l;
    long long total_magic = 0;

    // 读取输入
    scanf("%d %d", &N, &M);
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &Ini[i][j]);
        }
    }
    // 读取空行
    getchar();
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            scanf("%d", &Fin[i][j]);
        }
    }

    // 计算魔力
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            int diff = Ini[i][j] - Fin[i][j];
            if (diff > 0) {
                for (k = 0; k < N; k++) {
                    if (k != i) {
                        total_magic += (long long)diff * abs(k - i);
                    }
                }
                for (l = 0; l < M; l++) {
                    if (l != j) {
                        total_magic += (long long)diff * abs(l - j);
                    }
                }
            }
        }
    }

    // 输出结果
    printf("%lld\n", total_magic);

    return 0;
}
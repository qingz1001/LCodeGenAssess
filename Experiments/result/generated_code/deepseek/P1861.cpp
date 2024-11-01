#include <stdio.h>
#include <stdlib.h>

#define MAXN 200
#define MAXM 200

int main() {
    int N, M;
    int Ini[MAXN][MAXM], Fin[MAXN][MAXM];
    int i, j;
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
                total_magic += diff;
            }
        }
    }

    // 输出结果
    printf("%lld\n", total_magic);

    return 0;
}
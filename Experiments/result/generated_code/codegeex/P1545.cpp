#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1001
#define MAX_L 1000001

int N, L, A, B;
int S[MAX_N], E[MAX_N];
int dp[MAX_L];

int main() {
    scanf("%d %d", &N, &L);
    scanf("%d %d", &A, &B);

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &S[i], &E[i]);
    }

    // 初始化dp数组，dp[i]表示覆盖到位置i所需的最少喷灌器数量
    for (int i = 0; i <= L; i++) {
        dp[i] = -1;
    }

    // 初始位置0需要0个喷灌器
    dp[0] = 0;

    // 遍历每个位置，计算覆盖到该位置所需的最少喷灌器数量
    for (int i = 1; i <= L; i++) {
        // 遍历每个喷灌器的位置和射程
        for (int j = 0; j < N; j++) {
            int start = S[j] - B;
            int end = S[j] + B;
            if (start <= i && i <= end) {
                // 计算当前喷灌器覆盖到i位置所需的最少喷灌器数量
                for (int k = i - B; k <= i + B && k <= L; k++) {
                    if (dp[k] != -1) {
                        if (dp[i] == -1 || dp[i] > dp[k] + 1) {
                            dp[i] = dp[k] + 1;
                        }
                    }
                }
            }
        }
    }

    // 输出结果
    printf("%d\n", dp[L]);

    return 0;
}
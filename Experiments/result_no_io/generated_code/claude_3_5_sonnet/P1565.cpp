#include <stdio.h>
#include <stdlib.h>

#define MAX_N 200
#define MAX_M 200

long long a[MAX_N][MAX_M];
long long sum[MAX_N + 1][MAX_M + 1];

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    // 计算前缀和
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + a[i-1][j-1];
        }
    }

    int max_area = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            for (int k = i; k <= N; k++) {
                for (int l = j; l <= M; l++) {
                    long long area_sum = sum[k][l] - sum[i-1][l] - sum[k][j-1] + sum[i-1][j-1];
                    int area = (k - i + 1) * (l - j + 1);
                    if (area_sum > 0 && area > max_area) {
                        max_area = area;
                    }
                }
            }
        }
    }

    printf("%d\n", max_area);

    return 0;
}
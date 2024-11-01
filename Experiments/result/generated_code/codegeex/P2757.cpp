#include <stdio.h>
#include <stdbool.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        int A[N + 1];
        for (int i = 1; i <= N; i++) {
            scanf("%d", &A[i]);
        }

        // 判断是否存在等差子序列
        bool exists = false;
        for (int d = -N + 1; d <= N - 1; d++) {
            bool found = false;
            for (int i = 1; i <= N; i++) {
                if (A[i] + d > N || A[i] + 2 * d > N) continue;
                if (A[i] + d == A[i + 1] && A[i] + 2 * d == A[i + 2]) {
                    found = true;
                    break;
                }
            }
            if (found) {
                exists = true;
                break;
            }
        }

        if (exists) {
            printf("Y\n");
        } else {
            printf("N\n");
        }
    }
    return 0;
}
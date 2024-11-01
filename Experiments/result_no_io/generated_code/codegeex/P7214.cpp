#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

struct Solution {
    int T, L, R, C;
};

int compare(const void *a, const void *b) {
    struct Solution *solA = (struct Solution *)a;
    struct Solution *solB = (struct Solution *)b;
    if (solA->T != solB->T) {
        return solA->T - solB->T;
    } else {
        return solA->C - solB->C;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    struct Solution solutions[MAXM];
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d %d", &solutions[i].T, &solutions[i].L, &solutions[i].R, &solutions[i].C);
    }

    qsort(solutions, M, sizeof(struct Solution), compare);

    int dp[MAXN];
    memset(dp, 0x3f, sizeof(dp));
    dp[0] = 0;

    for (int i = 0; i < M; i++) {
        int T = solutions[i].T;
        int L = solutions[i].L;
        int R = solutions[i].R;
        int C = solutions[i].C;

        for (int j = L; j <= R; j++) {
            if (dp[j - 1] != 0x3f3f3f3f) {
                dp[j] = fmin(dp[j], dp[j - 1] + C);
            }
            if (dp[N - j] != 0x3f3f3f3f) {
                dp[N - j] = fmin(dp[N - j], dp[N - j + 1] + C);
            }
        }
    }

    int result = 0x3f3f3f3f;
    for (int i = 0; i <= N; i++) {
        if (dp[i] != 0x3f3f3f3f) {
            result = fmin(result, dp[i]);
        }
    }

    if (result == 0x3f3f3f3f) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
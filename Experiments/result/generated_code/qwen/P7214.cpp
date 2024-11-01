#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000000
#define MAXM 100000

typedef struct {
    int T;
    int L;
    int R;
    int C;
} Treatment;

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    Treatment treatments[MAXM];
    for (int i = 0; i < M; ++i) {
        scanf("%d %d %d %d", &treatments[i].T, &treatments[i].L, &treatments[i].R, &treatments[i].C);
    }

    // Sort treatments by start time T
    qsort(treatments, M, sizeof(Treatment), [](const void *a, const void *b) {
        return ((Treatment *)a)->T - ((Treatment *)b)->T;
    });

    // Initialize DP array
    long long dp[MAXN + 1];
    for (int i = 0; i <= N; ++i) {
        dp[i] = MAXN;
    }
    dp[0] = 0;

    for (int i = 0; i < M; ++i) {
        int T = treatments[i].T;
        int L = treatments[i].L;
        int R = treatments[i].R;
        int C = treatments[i].C;

        // Update DP array for the current treatment
        for (int j = N; j >= L; --j) {
            if (dp[j] != MAXN) {
                dp[j - L + R + 1] = dp[j] + C;
            }
        }
    }

    // Find the minimum cost to treat all villagers
    long long min_cost = MAXN;
    for (int i = 1; i <= N; ++i) {
        if (dp[i] != MAXN && dp[i] <= T) {
            min_cost = dp[i];
            break;
        }
    }

    if (min_cost == MAXN) {
        printf("-1\n");
    } else {
        printf("%lld\n", min_cost);
    }

    return 0;
}
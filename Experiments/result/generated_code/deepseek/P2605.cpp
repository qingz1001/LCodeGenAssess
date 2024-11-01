#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 20005
#define MAXK 105

int N, K;
long long D[MAXN], C[MAXN], S[MAXN], W[MAXN];
long long dp[MAXK][MAXN];

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 2; i <= N; i++) {
        scanf("%lld", &D[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &C[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &S[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &W[i]);
    }

    // Initialize dp array
    for (int i = 0; i <= K; i++) {
        for (int j = 0; j <= N; j++) {
            dp[i][j] = LLONG_MAX;
        }
    }
    dp[0][0] = 0;

    // Precompute the range of coverage for each village
    int cover_start[MAXN], cover_end[MAXN];
    for (int i = 1; i <= N; i++) {
        cover_start[i] = i;
        cover_end[i] = i;
        for (int j = i - 1; j >= 1; j--) {
            if (D[i] - D[j] <= S[i]) {
                cover_start[i] = j;
            } else {
                break;
            }
        }
        for (int j = i + 1; j <= N; j++) {
            if (D[j] - D[i] <= S[i]) {
                cover_end[i] = j;
            } else {
                break;
            }
        }
    }

    // DP transition
    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 0; j < i; j++) {
                long long cost = dp[k-1][j];
                if (cost == LLONG_MAX) continue;
                for (int l = j + 1; l <= i; l++) {
                    if (cover_start[l] <= j + 1 && cover_end[l] >= i) {
                        cost += C[l];
                    } else {
                        cost += W[l];
                    }
                }
                dp[k][i] = (dp[k][i] < cost) ? dp[k][i] : cost;
            }
        }
    }

    // Find the minimum cost
    long long min_cost = LLONG_MAX;
    for (int k = 1; k <= K; k++) {
        for (int i = 1; i <= N; i++) {
            if (dp[k][i] < min_cost) {
                min_cost = dp[k][i];
            }
        }
    }

    printf("%lld\n", min_cost);
    return 0;
}
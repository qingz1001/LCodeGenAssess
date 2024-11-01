#include <stdio.h>
#include <stdlib.h>

#define MAXN 200000
#define MAXM 100000

typedef struct {
    int a, b;
} Photo;

Photo photos[MAXM];
int left_bound[MAXN + 1], right_bound[MAXN + 1];
int dp[MAXN + 1];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &photos[i].a, &photos[i].b);
    }

    // Initialize bounds
    for (int i = 1; i <= N; i++) {
        left_bound[i] = -1;
        right_bound[i] = N + 1;
    }

    // Update bounds based on photos
    for (int i = 0; i < M; i++) {
        int a = photos[i].a;
        int b = photos[i].b;
        for (int j = a; j <= b; j++) {
            if (j == a) {
                left_bound[j] = max(left_bound[j], a);
            } else {
                left_bound[j] = max(left_bound[j], a + 1);
            }
            if (j == b) {
                right_bound[j] = min(right_bound[j], b);
            } else {
                right_bound[j] = min(right_bound[j], b - 1);
            }
        }
    }

    // Dynamic programming to find the maximum number of spotted cows
    dp[0] = 0;
    for (int i = 1; i <= N; i++) {
        dp[i] = -1;
        for (int j = left_bound[i]; j <= right_bound[i]; j++) {
            if (dp[j - 1] != -1) {
                dp[i] = max(dp[i], dp[j - 1] + 1);
            }
        }
    }

    printf("%d\n", dp[N]);

    return 0;
}
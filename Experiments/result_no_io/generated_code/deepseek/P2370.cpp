#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define INF 1000000000

int n, p, S;
int W[MAXN], V[MAXN];

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int can_achieve(int L) {
    int dp[MAXN] = {0};
    for (int i = 0; i < n; i++) {
        if (W[i] <= L) {
            for (int j = S; j >= W[i]; j--) {
                if (dp[j - W[i]] + V[i] > dp[j]) {
                    dp[j] = dp[j - W[i]] + V[i];
                }
            }
        }
    }
    return dp[S] >= p;
}

int main() {
    scanf("%d %d %d", &n, &p, &S);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &W[i], &V[i]);
    }

    qsort(W, n, sizeof(int), compare);

    int left = 1, right = W[n - 1], mid;
    int result = INF;

    while (left <= right) {
        mid = (left + right) / 2;
        if (can_achieve(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (result == INF) {
        printf("No Solution!\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
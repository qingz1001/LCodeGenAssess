#include <stdio.h>
#include <stdlib.h>

#define MOD 18446744073709551616ULL

typedef struct {
    unsigned long long *dp;
    int *parent;
} DPInfo;

void initDP(DPInfo *dp, int n) {
    dp->dp = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    dp->parent = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; ++i) {
        dp->dp[i] = 0;
        dp->parent[i] = -1;
    }
}

void freeDP(DPInfo *dp) {
    free(dp->dp);
    free(dp->parent);
}

void updateDP(DPInfo *dp, int i, int j) {
    if (i == 0 && j == 0) {
        dp->dp[0] = 1;
        dp->parent[0] = 0;
        return;
    }
    if (j >= 0 && j <= i) {
        dp->dp[j] = (dp->dp[j] + dp->dp[j - 1]) % MOD;
        dp->parent[j] = j - 1;
    }
    if (j + 1 <= i) {
        dp->dp[j + 1] = (dp->dp[j + 1] + dp->dp[j]) % MOD;
        dp->parent[j + 1] = j;
    }
}

void printSequence(DPInfo *dp, int n, int sum) {
    if (sum == 0) {
        printf("0");
        for (int i = 1; i <= n; ++i) {
            printf(" 0");
        }
        printf("\n");
        return;
    }
    int currentSum = 0;
    while (currentSum != sum) {
        int nextIndex = dp->parent[currentSum];
        if (nextIndex == currentSum - 1) {
            printf("0");
        } else {
            printf("-1");
        }
        currentSum += (nextIndex - currentSum);
    }
    for (int i = 0; i < n; ++i) {
        printf(" 0");
    }
    printf("\n");
}

int main() {
    int n, s;
    scanf("%d %d", &n, &s);

    DPInfo dp;
    initDP(&dp, n);

    updateDP(&dp, 0, 0);

    for (int i = 1; i <= n; ++i) {
        for (int j = i; j >= 0; --j) {
            updateDP(&dp, i, j);
        }
    }

    unsigned long long totalSequences = dp.dp[s];
    printf("%llu\n", totalSequences);

    if (totalSequences > 0) {
        for (int i = 0; i < 100 && i < totalSequences; ++i) {
            printSequence(&dp, n, s);
        }
    }

    freeDP(&dp);
    return 0;
}
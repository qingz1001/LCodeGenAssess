#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_N 1000
#define INF LLONG_MAX

typedef long long ll;

ll prices[MAX_N];
ll dp[MAX_N];
ll ways[MAX_N];

struct Recipe {
    int A, B, C;
} recipes[MAX_N];

int main() {
    int N;
    scanf("%d", &N);

    // Read the prices of each type of potion
    for (int i = 0; i < N; i++) {
        scanf("%lld", &prices[i]);
        dp[i] = INF;
        ways[i] = 0;
    }

    dp[0] = prices[0];
    ways[0] = 1;

    // Read the recipes
    int recipeCount = 0;
    while (1) {
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        if (A == 0 && B == 0 && C == 0) break;
        recipes[recipeCount++] = (struct Recipe){A - 1, B - 1, C - 1};
    }

    // Process each recipe
    for (int i = 0; i < recipeCount; i++) {
        int A = recipes[i].A;
        int B = recipes[i].B;
        int C = recipes[i].C;

        ll newCost = dp[A] + dp[B];
        if (newCost < dp[C]) {
            dp[C] = newCost;
            ways[C] = ways[A] * ways[B];
        } else if (newCost == dp[C]) {
            ways[C] += ways[A] * ways[B];
        }
    }

    printf("%lld %lld\n", dp[0], ways[0]);

    return 0;
}
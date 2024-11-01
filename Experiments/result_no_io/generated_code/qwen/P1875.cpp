#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000
#define INF 1e9

typedef struct {
    int a, b, c;
} Recipe;

int main() {
    int N;
    scanf("%d", &N);
    int prices[MAX_N];
    for (int i = 0; i < N; ++i) {
        scanf("%d", &prices[i]);
    }

    Recipe recipes[2 * MAX_N];
    int recipe_count = 0;
    while (1) {
        int a, b, c;
        if (scanf("%d %d %d", &a, &b, &c) != 3) break;
        recipes[recipe_count].a = a;
        recipes[recipe_count].b = b;
        recipes[recipe_count].c = c;
        ++recipe_count;
    }

    long long dp[MAX_N];
    for (int i = 0; i < N; ++i) {
        dp[i] = prices[i];
    }
    dp[N] = 0;

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j < recipe_count; ++j) {
            int a = recipes[j].a, b = recipes[j].b, c = recipes[j].c;
            if (i >= a && i >= b) {
                dp[c] = fmin(dp[c], dp[i - a] + dp[i - b]);
            }
        }
    }

    long long min_cost = dp[0];
    long long count = 0;
    for (int i = 0; i <= N; ++i) {
        if (dp[i] == min_cost) {
            count += 1;
        }
    }

    printf("%lld %lld\n", min_cost, count);

    return 0;
}
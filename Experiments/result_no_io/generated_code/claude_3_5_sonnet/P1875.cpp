#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000

long long dp[MAX_N];
long long count[MAX_N];
int price[MAX_N];
int recipe[MAX_N][MAX_N];
int N;

void solve() {
    for (int i = 0; i < N; i++) {
        dp[i] = price[i];
        count[i] = 1;
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                if (recipe[j][k] == i) {
                    long long new_cost = dp[j] + dp[k];
                    if (new_cost < dp[i]) {
                        dp[i] = new_cost;
                        count[i] = count[j] * count[k];
                    } else if (new_cost == dp[i]) {
                        count[i] += count[j] * count[k];
                    }
                }
            }
        }
    }

    printf("%lld %lld\n", dp[0], count[0]);
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &price[i]);
    }

    memset(recipe, -1, sizeof(recipe));

    int a, b, c;
    while (scanf("%d %d %d", &a, &b, &c) == 3) {
        recipe[a][b] = c;
        recipe[b][a] = c;
    }

    solve();

    return 0;
}
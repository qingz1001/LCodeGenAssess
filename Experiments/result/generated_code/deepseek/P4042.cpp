#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define MAXR 1000005

typedef long long ll;

typedef struct {
    ll S, K;
    int R;
    int *spawns;
} Monster;

Monster monsters[MAXN];
ll dp[MAXN];
int N;

void read_input() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld %lld %d", &monsters[i].S, &monsters[i].K, &monsters[i].R);
        monsters[i].spawns = (int *)malloc(sizeof(int) * monsters[i].R);
        for (int j = 0; j < monsters[i].R; j++) {
            scanf("%d", &monsters[i].spawns[j]);
        }
    }
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll dfs(int i) {
    if (dp[i] != -1) return dp[i];

    ll min_cost = monsters[i].K;
    ll sum_spawn_cost = 0;

    for (int j = 0; j < monsters[i].R; j++) {
        sum_spawn_cost += dfs(monsters[i].spawns[j]);
    }

    min_cost = min(min_cost, monsters[i].S + sum_spawn_cost);
    dp[i] = min_cost;
    return min_cost;
}

int main() {
    read_input();

    for (int i = 1; i <= N; i++) {
        dp[i] = -1;
    }

    ll result = dfs(1);
    printf("%lld\n", result);

    for (int i = 1; i <= N; i++) {
        free(monsters[i].spawns);
    }

    return 0;
}
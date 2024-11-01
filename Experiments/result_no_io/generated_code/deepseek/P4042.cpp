#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define MAXR 1000005

typedef long long ll;

struct Monster {
    ll S, K;
    int R;
    int *spawns;
};

struct Monster monsters[MAXN];
ll dp[MAXN];
int visited[MAXN];
int N;

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll dfs(int i) {
    if (visited[i]) return dp[i];
    visited[i] = 1;

    dp[i] = monsters[i].K;
    ll sum = 0;
    for (int j = 0; j < monsters[i].R; j++) {
        sum += dfs(monsters[i].spawns[j]);
    }
    dp[i] = min(dp[i], sum + monsters[i].S);

    return dp[i];
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld %lld %d", &monsters[i].S, &monsters[i].K, &monsters[i].R);
        monsters[i].spawns = (int *)malloc(monsters[i].R * sizeof(int));
        for (int j = 0; j < monsters[i].R; j++) {
            scanf("%d", &monsters[i].spawns[j]);
        }
    }

    ll result = dfs(1);
    printf("%lld\n", result);

    for (int i = 1; i <= N; i++) {
        free(monsters[i].spawns);
    }

    return 0;
}
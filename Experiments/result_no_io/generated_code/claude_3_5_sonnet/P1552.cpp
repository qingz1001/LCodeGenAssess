#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_M 1000000000

typedef long long ll;

int N, M;
int B[MAX_N], C[MAX_N], L[MAX_N];
int children[MAX_N][2], child_count[MAX_N];
ll dp[MAX_N][2];

void add_child(int parent, int child) {
    if (child_count[parent] < 2) {
        children[parent][child_count[parent]] = child;
    }
    child_count[parent]++;
}

ll max(ll a, ll b) {
    return a > b ? a : b;
}

void dfs(int node) {
    dp[node][0] = 0;
    dp[node][1] = C[node];

    for (int i = 0; i < child_count[node]; i++) {
        int child = children[node][i];
        dfs(child);

        dp[node][0] += max(dp[child][0], dp[child][1]);
        if (dp[node][1] <= M) {
            dp[node][1] += dp[child][0];
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);

    for (int i = 1; i <= N; i++) {
        scanf("%d %d %d", &B[i], &C[i], &L[i]);
        add_child(B[i], i);
    }

    dfs(0);

    ll result = 0;
    for (int i = 0; i <= N; i++) {
        if (dp[i][1] <= M) {
            result = max(result, (ll)L[i] * (dp[i][1] / C[i]));
        }
        result = max(result, (ll)L[i] * (dp[i][0] / C[i]));
    }

    printf("%lld\n", result);

    return 0;
}
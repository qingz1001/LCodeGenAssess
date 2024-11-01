#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

ll max(ll a, ll b) {
    return a > b ? a : b;
}

ll min(ll a, ll b) {
    return a < b ? a : b;
}

int main() {
    int N;
    scanf("%d", &N);
    ll *a = (ll *)malloc(sizeof(ll) * N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }

    ll **dp = (ll **)malloc(sizeof(ll *) * N);
    for (int i = 0; i < N; i++) {
        dp[i] = (ll *)malloc(sizeof(ll) * 2);
    }

    dp[0][0] = a[0];
    dp[0][1] = 0;

    for (int i = 1; i < N; i++) {
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]) + a[i];
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]);
    }

    ll first_player = max(dp[N-1][0], dp[N-1][1]);
    ll second_player = min(dp[N-1][0], dp[N-1][1]);

    printf("%lld %lld\n", first_player, second_player);

    for (int i = 0; i < N; i++) {
        free(dp[i]);
    }
    free(dp);
    free(a);

    return 0;
}
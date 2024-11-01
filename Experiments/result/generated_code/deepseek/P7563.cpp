#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define INF 1000000000000000000LL

typedef long long ll;

typedef struct {
    int a, h, c;
} Player;

Player players[MAXN];
ll dp[MAXN];

int compare(const void *a, const void *b) {
    return ((Player *)a)->h - ((Player *)b)->h;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &players[i].a, &players[i].h, &players[i].c);
    }

    qsort(players + 1, n, sizeof(Player), compare);

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        ll min_cost = INF;
        for (int j = i - 1; j >= 0; j--) {
            if (players[j].h <= players[i].h) {
                min_cost = (ll)players[j].c;
                break;
            }
        }
        dp[i] = dp[players[i].a - 1] + min_cost;
    }

    printf("%lld\n", dp[n]);

    return 0;
}
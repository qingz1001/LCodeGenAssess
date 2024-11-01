#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 200005
#define INF INT_MAX

typedef struct {
    int a, h, c;
} Player;

Player players[MAXN];
int dp[MAXN];

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d %d %d", &players[i].a, &players[i].h, &players[i].c);
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }

    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        int max_h = 0;
        for (int j = i; j >= 1; j--) {
            max_h = max_h > players[j].h ? max_h : players[j].h;
            if (players[j].a <= j) {
                dp[i] = min(dp[i], dp[j - 1] + players[j].c);
            }
        }
    }

    printf("%d\n", dp[n]);

    return 0;
}
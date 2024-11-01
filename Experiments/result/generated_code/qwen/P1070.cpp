#include <stdio.h>
#include <stdlib.h>

#define MAXN 1005
#define MAXM 1005

int n, m, p;
int coins[MAXN][MAXM];
int cost[MAXN];

struct Robot {
    int factory;
    int steps_left;
};

void init() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &coins[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &cost[i]);
    }
}

int collect_coins(int start_factory, int steps) {
    int total_coins = 0;
    for (int step = 0; step < steps; ++step) {
        total_coins += coins[start_factory][step % m];
        start_factory = (start_factory + 1) % n;
    }
    return total_coins;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    init();

    int max_coins = -1;
    for (int i = 0; i < n; ++i) {
        for (int steps = 1; steps <= p; ++steps) {
            int current_coins = collect_coins(i, steps);
            if (current_coins > max_coins) {
                max_coins = current_coins;
            }
        }
    }

    printf("%d\n", max_coins);

    return 0;
}
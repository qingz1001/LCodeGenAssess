#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000000
#define MAXM 1000000

int N, M;
int C[MAXN];
int cost[MAXM];

void solve() {
    for (int i = 0; i < M; i++) {
        cost[i] = INT_MAX;
    }

    for (int i = 0; i < N; i++) {
        int current_color = C[i] - 1;
        int current_cost = 0;
        for (int j = i; j < N; j++) {
            if (C[j] - 1 == current_color) {
                current_cost += (j - i + 1);
                if (current_cost < cost[current_color]) {
                    cost[current_color] = current_cost;
                }
            }
        }
    }

    for (int i = 0; i < M; i++) {
        printf("%d\n", cost[i]);
    }
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        scanf("%d", &C[i]);
    }

    solve();

    return 0;
}
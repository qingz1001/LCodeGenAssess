#include <stdio.h>
#include <stdlib.h>

#define MAXN 505

int n;
long long adj[MAXN][MAXN];
int army[2][MAXN / 2];
long long max_value = -1;

void dfs(int turn, int free_count) {
    if (free_count == 0) {
        long long value = 0;
        for (int i = 0; i < n / 2; i++) {
            value += adj[army[0][i]][army[1][i]];
        }
        if (value > max_value) {
            max_value = value;
        }
        return;
    }

    int current_army = turn % 2;
    int next_turn = (turn + 1) % 2;

    for (int i = 0; i < n - free_count; i++) {
        if (adj[army[current_army][i]][army[next_turn][i]] == -1) continue;

        int temp = adj[army[current_army][i]][army[next_turn][i]];
        adj[army[current_army][i]][army[next_turn][i]] = -1;
        adj[army[next_turn][i]][army[current_army][i]] = -1;

        army[current_army][n - free_count] = i + 1;
        dfs(next_turn, free_count - 1);

        adj[army[current_army][i]][army[next_turn][i]] = temp;
        adj[army[next_turn][i]][army[current_army][i]] = temp;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            scanf("%lld", &adj[i][j]);
        }
    }

    for (int i = 0; i < n / 2; i++) {
        army[0][i] = i + 1;
    }

    dfs(1, n / 2 - 1);

    if (max_value != -1) {
        printf("1\n");
        printf("%lld\n", max_value);
    } else {
        printf("0\n");
    }

    return 0;
}
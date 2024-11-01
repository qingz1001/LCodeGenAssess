#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 3000
#define MAX_R 8000

int n, p, r;
int bribe[MAX_N + 1];
int graph[MAX_N + 1][MAX_N + 1];
int visited[MAX_N + 1];

void dfs(int x) {
    visited[x] = 1;
    for (int i = 1; i <= n; i++) {
        if (graph[x][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    scanf("%d", &n);
    scanf("%d", &p);

    memset(bribe, -1, sizeof(bribe));
    for (int i = 0; i < p; i++) {
        int spy, amount;
        scanf("%d %d", &spy, &amount);
        bribe[spy] = amount;
    }

    scanf("%d", &r);
    for (int i = 0; i < r; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a][b] = 1;
    }

    int start = 0;
    for (int i = 1; i <= n; i++) {
        if (bribe[i] != -1) {
            start = i;
            break;
        }
    }

    if (start == 0) {
        printf("NO\n1\n");
        return 0;
    }

    dfs(start);

    int all_visited = 1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            all_visited = 0;
            printf("NO\n%d\n", i);
            return 0;
        }
    }

    if (all_visited) {
        long long total_bribe = 0;
        for (int i = 1; i <= n; i++) {
            if (bribe[i] != -1) {
                total_bribe += bribe[i];
            }
        }
        printf("YES\n%lld\n", total_bribe);
    }

    return 0;
}
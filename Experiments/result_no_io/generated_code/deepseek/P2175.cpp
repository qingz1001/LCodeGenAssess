#include <stdio.h>
#include <stdbool.h>

#define MAXN 2000

int n;
int trust[MAXN + 1][MAXN + 1];
int team[MAXN + 1];
bool visited[MAXN + 1];

bool dfs(int u, int t) {
    team[u] = t;
    visited[u] = true;
    for (int i = 1; i <= n; i++) {
        if (trust[u][i]) {
            if (team[i] == t) return false;
            if (!visited[i] && !dfs(i, 3 - t)) return false;
        }
    }
    return true;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x;
        while (scanf("%d", &x) && x != 0) {
            trust[i][x] = 1;
            trust[x][i] = 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i, 1)) {
                printf("No solution\n");
                return 0;
            }
        }
    }

    int count1 = 0, count2 = 0;
    for (int i = 1; i <= n; i++) {
        if (team[i] == 1) count1++;
        else count2++;
    }

    if (count1 < count2) printf("%d %d\n", count1, count2);
    else printf("%d %d\n", count2, count1);

    return 0;
}
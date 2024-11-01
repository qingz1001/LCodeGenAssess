#include <stdio.h>
#include <stdbool.h>

#define MAXN 101

int n;
bool known[MAXN][MAXN];

void input() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            known[i][j] = false;
        }
    }
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        while (x != 0) {
            known[i][x] = true;
            scanf("%d", &x);
        }
    }
}

bool dfs(int u, bool color, bool visited[], bool group1[], bool group2[]) {
    visited[u] = true;
    if (color) {
        group1[u] = true;
    } else {
        group2[u] = true;
    }
    for (int v = 1; v <= n; v++) {
        if (known[u][v] && !visited[v]) {
            if (!dfs(v, !color, visited, group1, group2)) {
                return false;
            }
        } else if (known[u][v] && visited[v] && group1[u] == group1[v]) {
            return false;
        }
    }
    return true;
}

void solve() {
    bool visited[MAXN], group1[MAXN], group2[MAXN];
    for (int i = 1; i <= n; i++) {
        visited[i] = false;
        group1[i] = false;
        group2[i] = false;
    }
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            if (!dfs(i, true, visited, group1, group2)) {
                printf("No solution\n");
                return;
            }
        }
    }
    int count1 = 0, count2 = 0;
    for (int i = 1; i <= n; i++) {
        if (group1[i]) count1++;
        if (group2[i]) count2++;
    }
    if (count1 == 0 || count2 == 0) {
        printf("No solution\n");
        return;
    }
    printf("%d ", count1);
    for (int i = 1; i <= n; i++) {
        if (group1[i]) printf("%d ", i);
    }
    printf("\n%d ", count2);
    for (int i = 1; i <= n; i++) {
        if (group2[i]) printf("%d ", i);
    }
    printf("\n");
}

int main() {
    input();
    solve();
    return 0;
}
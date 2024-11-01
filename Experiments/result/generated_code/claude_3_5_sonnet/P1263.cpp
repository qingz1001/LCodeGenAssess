#include <stdio.h>
#include <string.h>

#define MAX_N 205
#define MAX_M 205

int m, n;
int castle[MAX_M][MAX_N];
int row[MAX_M], col[MAX_N];
int match[MAX_N];
int used[MAX_N];

int dfs(int x) {
    for (int y = 1; y <= n; y++) {
        if (castle[x][y] == 0 && !used[y]) {
            used[y] = 1;
            if (match[y] == 0 || dfs(match[y])) {
                match[y] = x;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &castle[i][j]);
            if (castle[i][j] == 2) {
                row[i] = col[j] = 1;
            }
        }
    }
    
    int count = 0;
    for (int i = 1; i <= m; i++) {
        if (!row[i]) {
            memset(used, 0, sizeof(used));
            if (dfs(i)) count++;
        }
    }
    
    printf("%d\n", count);
    
    for (int y = 1; y <= n; y++) {
        if (match[y]) {
            printf("%d %d\n", match[y], y);
        }
    }
    
    return 0;
}
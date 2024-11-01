#include <stdio.h>
#include <string.h>

#define MAX_N 200
#define MAX_M 200

int m, n;
int castle[MAX_M][MAX_N];
int left[MAX_M][MAX_N], up[MAX_M][MAX_N], right[MAX_M][MAX_N], down[MAX_M][MAX_N];
int match[MAX_N];
int used[MAX_N];

int dfs(int u) {
    for (int v = 0; v < n; v++) {
        if (right[u][v] && !used[v]) {
            used[v] = 1;
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &m, &n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &castle[i][j]);
        }
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (castle[i][j] == 0) {
                if (j == 0 || castle[i][j-1] == 2) left[i][j] = j;
                else left[i][j] = left[i][j-1];
                
                if (i == 0 || castle[i-1][j] == 2) up[i][j] = i;
                else up[i][j] = up[i-1][j];
            }
        }
    }
    
    for (int i = m-1; i >= 0; i--) {
        for (int j = n-1; j >= 0; j--) {
            if (castle[i][j] == 0) {
                if (j == n-1 || castle[i][j+1] == 2) right[i][j] = j;
                else right[i][j] = right[i][j+1];
                
                if (i == m-1 || castle[i+1][j] == 2) down[i][j] = i;
                else down[i][j] = down[i+1][j];
            }
        }
    }
    
    int count = 0;
    memset(match, -1, sizeof(match));
    
    for (int i = 0; i < m; i++) {
        memset(used, 0, sizeof(used));
        if (dfs(i)) count++;
    }
    
    printf("%d\n", count);
    
    for (int j = 0; j < n; j++) {
        if (match[j] != -1) {
            printf("%d %d\n", match[j] + 1, j + 1);
        }
    }
    
    return 0;
}
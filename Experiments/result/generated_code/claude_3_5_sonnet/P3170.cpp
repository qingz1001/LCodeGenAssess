#include <stdio.h>
#include <string.h>

#define MAX_N 30
#define MAX_M 30

char grid[MAX_N][MAX_M];
int n, m;
long long result = 0;

void dfs(int count) {
    if (count == 3) {
        result++;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.') continue;

            for (int k = i + 1; k < n; k++) {
                if (grid[k][j] != '.') break;
                for (int l = j + 1; l < m; l++) {
                    if (grid[i][l] != '.') break;
                    
                    grid[i][j] = 'L';
                    for (int x = i + 1; x <= k; x++) grid[x][j] = 'L';
                    for (int y = j + 1; y <= l; y++) grid[i][y] = 'L';
                    
                    dfs(count + 1);
                    
                    grid[i][j] = '.';
                    for (int x = i + 1; x <= k; x++) grid[x][j] = '.';
                    for (int y = j + 1; y <= l; y++) grid[i][y] = '.';
                }
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", grid[i]);
    }
    
    dfs(0);
    
    printf("%lld\n", result);
    return 0;
}
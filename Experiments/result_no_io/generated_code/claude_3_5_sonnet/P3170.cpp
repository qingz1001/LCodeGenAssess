#include <stdio.h>
#include <string.h>

#define MAXN 31
#define MAXM 31

char grid[MAXN][MAXM];
int n, m, count = 0;

void dfs(int l) {
    if (l == 3) {
        count++;
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] != '.') continue;

            for (int h = 1; h < n - i; h++) {
                for (int w = 1; w < m - j; w++) {
                    int valid = 1;
                    for (int x = i; x <= i + h && valid; x++) {
                        if (grid[x][j] != '.') valid = 0;
                    }
                    for (int y = j; y <= j + w && valid; y++) {
                        if (grid[i][y] != '.') valid = 0;
                    }
                    
                    if (valid) {
                        for (int x = i; x <= i + h; x++) grid[x][j] = 'L';
                        for (int y = j; y <= j + w; y++) grid[i][y] = 'L';
                        
                        dfs(l + 1);
                        
                        for (int x = i; x <= i + h; x++) grid[x][j] = '.';
                        for (int y = j; y <= j + w; y++) grid[i][y] = '.';
                    }
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
    
    printf("%d\n", count);
    return 0;
}
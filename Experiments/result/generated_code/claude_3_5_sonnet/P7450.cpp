#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 233
#define MAX_M 233
#define INF 0x3f3f3f3f

int n, m, k;
int c[MAX_N][MAX_M], a[MAX_N][MAX_M];
int vis[MAX_N][MAX_M], cnt[MAX_N*MAX_M+1];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int dfs(int x, int y, int mid, int *types, int *size) {
    if (x < 0 || x >= n || y < 0 || y >= m || vis[x][y] || c[x][y] == -1 || a[x][y] > mid)
        return 0;
    
    vis[x][y] = 1;
    (*size)++;
    if (cnt[c[x][y]] == 0) (*types)++;
    cnt[c[x][y]]++;
    
    for (int i = 0; i < 4; i++) {
        dfs(x + dx[i], y + dy[i], mid, types, size);
    }
    
    return *types >= k;
}

int check(int mid) {
    int min_size = INF;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (c[i][j] != -1 && a[i][j] <= mid) {
                memset(vis, 0, sizeof(vis));
                memset(cnt, 0, sizeof(cnt));
                int types = 0, size = 0;
                if (dfs(i, j, mid, &types, &size) && size < min_size) {
                    min_size = size;
                }
            }
        }
    }
    
    return min_size == INF ? -1 : min_size;
}

int main() {
    int T;
    scanf("%d", &T);
    
    while (T--) {
        scanf("%d %d %d", &n, &m, &k);
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &c[i][j]);
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        
        int left = 0, right = 1000000, min_size = -1, min_median = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int size = check(mid);
            
            if (size != -1) {
                min_size = size;
                min_median = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        printf("%d %d\n", min_size, min_median);
    }
    
    return 0;
}
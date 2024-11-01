#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 1000
#define MAX_M 1000
#define MAX_K 100000

int n, m, k;
int h[MAX_N][MAX_M];
int x[MAX_K], y[MAX_K];
bool is_mountain[MAX_N][MAX_M];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool is_valid(int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m;
}

void find_mountains() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            is_mountain[i][j] = true;
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (is_valid(ni, nj) && h[ni][nj] > h[i][j]) {
                    is_mountain[i][j] = false;
                    break;
                }
            }
        }
    }
}

int find_nearest_mountain(int start_x, int start_y) {
    for (int dist = 0; dist < n; dist++) {
        int cur_x = start_x - dist;
        if (cur_x < 0) break;
        
        for (int dy = -dist; dy <= dist; dy++) {
            int cur_y = start_y + dy;
            if (is_valid(cur_x, cur_y) && is_mountain[cur_x][cur_y]) {
                return dist;
            }
        }
    }
    return -1;
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &h[i][j]);
        }
    }
    
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &x[i], &y[i]);
        x[i]--; y[i]--;
    }
    
    find_mountains();
    
    for (int i = 0; i < k; i++) {
        int result = find_nearest_mountain(x[i], y[i]);
        if (result == -1) {
            printf("Pool Babingbaboom!\n");
        } else {
            printf("%d\n", result);
        }
    }
    
    return 0;
}
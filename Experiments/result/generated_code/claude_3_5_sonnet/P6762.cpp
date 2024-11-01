#include <stdio.h>
#include <string.h>

#define N 6
#define M 4

char a[N][N], b[N][N];
int h, used[N][N], cnt;
long long ans;

int check(int x, int y, int c) {
    if (x < 0 || x >= N || y < 0 || y >= N) return 0;
    return !used[x][y] && (a[x][y] == '.' || a[x][y] == c) && (b[y][N-1-x] == '.' || b[y][N-1-x] == c);
}

void dfs(int x, int y) {
    if (y == N) {
        x++, y = 0;
    }
    if (x == N) {
        ans++;
        return;
    }
    if (used[x][y]) {
        dfs(x, y+1);
        return;
    }
    
    int dx[] = {0, 0, 1, 1};
    int dy[] = {0, 1, 0, 1};
    char colors[] = {'W', 'G', 'B'};
    
    for (int c = 0; c < 3; c++) {
        int flag = 1;
        for (int k = 0; k < M; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (!check(nx, ny, colors[c])) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            for (int k = 0; k < M; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                used[nx][ny] = 1;
                if (a[nx][ny] == '.') a[nx][ny] = colors[c];
                if (b[ny][N-1-nx] == '.') b[ny][N-1-nx] = colors[c];
            }
            dfs(x, y+2);
            for (int k = 0; k < M; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                used[nx][ny] = 0;
                if (a[nx][ny] == colors[c]) a[nx][ny] = '.';
                if (b[ny][N-1-nx] == colors[c]) b[ny][N-1-nx] = '.';
            }
        }
    }
    
    dfs(x, y+1);
}

int main() {
    scanf("%d", &h);
    for (int i = 0; i < h; i++) {
        scanf("%s", a[i]);
    }
    for (int i = 0; i < h; i++) {
        scanf("%s", b[i]);
    }
    
    dfs(0, 0);
    
    printf("%lld\n", ans);
    
    return 0;
}
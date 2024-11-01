#include <stdio.h>
#include <string.h>

#define MAXN 20
#define MAXK 20

int n, k, h;
int color[MAXK];
int board[MAXN][MAXN];
long long ans;

void dfs(int x, int y, int remain) {
    if (remain == 0) {
        ans++;
        return;
    }
    if (y == n) {
        x++, y = 0;
    }
    if (x == n) return;

    dfs(x, y + 1, remain);

    int can_place = 1;
    for (int i = 0; i < x; i++) {
        if (board[i][y]) {
            can_place = 0;
            break;
        }
    }
    for (int j = 0; j < y; j++) {
        if (board[x][j]) {
            can_place = 0;
            break;
        }
    }

    if (can_place) {
        for (int c = 0; c < h; c++) {
            if (color[c] > 0) {
                board[x][y] = c + 1;
                color[c]--;
                dfs(x, y + 1, remain - 1);
                color[c]++;
                board[x][y] = 0;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &h);
    for (int i = 0; i < h; i++) {
        scanf("%d", &color[i]);
    }

    memset(board, 0, sizeof(board));
    ans = 0;
    dfs(0, 0, k);

    printf("%lld\n", ans);
    return 0;
}
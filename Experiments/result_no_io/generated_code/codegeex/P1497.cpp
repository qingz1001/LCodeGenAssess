#include <stdio.h>

int n, k, h;
int colors[21];
int used[21][21];
int ans = 0;

void dfs(int x, int y, int count) {
    if (count == k) {
        ans++;
        return;
    }
    if (y == n) {
        y = 0;
        x++;
    }
    if (x == n) return;
    for (int i = 1; i <= h; i++) {
        if (colors[i] > 0) {
            bool valid = true;
            for (int j = 0; j < n; j++) {
                if (used[x][j] == i) {
                    valid = false;
                    break;
                }
            }
            for (int j = 0; j < n; j++) {
                if (used[j][y] == i) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                used[x][y] = i;
                colors[i]--;
                dfs(x, y + 1, count + 1);
                colors[i]++;
                used[x][y] = 0;
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &k, &h);
    for (int i = 1; i <= h; i++) {
        scanf("%d", &colors[i]);
    }
    dfs(0, 0, 0);
    printf("%d\n", ans);
    return 0;
}
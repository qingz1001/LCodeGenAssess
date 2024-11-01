#include <stdio.h>

int n, k;
int x[55], y[55];
int min_area = 0x7fffffff;

void dfs(int cur, int used, int area) {
    if (cur > n) {
        if (used == k && area < min_area) {
            min_area = area;
        }
        return;
    }
    if (used >= k) return;

    int min_x = 0x7fffffff, max_x = 0;
    int min_y = 0x7fffffff, max_y = 0;
    for (int i = cur; i <= n; i++) {
        if (x[i] < min_x) min_x = x[i];
        if (x[i] > max_x) max_x = x[i];
        if (y[i] < min_y) min_y = y[i];
        if (y[i] > max_y) max_y = y[i];
    }
    int rect_area = (max_x - min_x) * (max_y - min_y);
    dfs(cur + 1, used + 1, area + rect_area);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &x[i], &y[i]);
    }
    dfs(1, 0, 0);
    printf("%d\n", min_area);
    return 0;
}
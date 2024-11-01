#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXC 1000005

int n, m;
int a[MAXN];
int color_count[MAXC];
int color_map[MAXC];
int color_size[MAXC];
int color_head[MAXC];
int color_next[MAXN];
int color_prev[MAXN];
int segments;

void init() {
    for (int i = 1; i <= n; i++) {
        color_count[a[i]]++;
        color_map[a[i]] = a[i];
        color_size[a[i]]++;
        color_next[i] = -1;
        color_prev[i] = -1;
    }
    segments = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] != a[i + 1]) segments++;
    }
}

void merge(int x, int y) {
    if (x == y) return;
    if (color_size[x] > color_size[y]) {
        int temp = x;
        x = y;
        y = temp;
    }
    if (color_size[x] == 0) return;

    for (int i = color_head[x]; i != -1; i = color_next[i]) {
        if (a[i] == x && a[i - 1] == y) segments--;
        if (a[i] == x && a[i + 1] == y) segments--;
    }

    for (int i = color_head[x]; i != -1; i = color_next[i]) {
        a[i] = y;
        if (color_next[i] == -1) {
            color_next[i] = color_head[y];
            if (color_head[y] != -1) color_prev[color_head[y]] = i;
            color_head[y] = color_head[x];
            break;
        }
    }

    color_size[y] += color_size[x];
    color_size[x] = 0;
    color_head[x] = -1;
    color_map[x] = y;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    init();

    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            merge(color_map[x], color_map[y]);
        } else if (op == 2) {
            printf("%d\n", segments);
        }
    }

    return 0;
}
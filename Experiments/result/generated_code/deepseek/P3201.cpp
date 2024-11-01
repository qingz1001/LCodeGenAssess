#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXC 1000005

int n, m;
int color[MAXN];
int color_count[MAXC];
int color_head[MAXC];
int color_next[MAXN];
int color_prev[MAXN];
int color_map[MAXC];
int color_segments;

void init() {
    for (int i = 1; i <= n; i++) {
        color_count[color[i]]++;
        if (i == 1 || color[i] != color[i - 1]) {
            color_segments++;
        }
        color_next[i] = color_head[color[i]];
        color_head[color[i]] = i;
        if (color_next[i]) {
            color_prev[color_next[i]] = i;
        }
    }
}

void merge(int x, int y) {
    if (x == y) return;
    if (color_count[color_map[x]] > color_count[color_map[y]]) {
        int temp = x;
        x = y;
        y = temp;
    }
    if (color_count[color_map[x]] == 0) return;

    for (int i = color_head[color_map[x]]; i; i = color_next[i]) {
        if (color[i] == x && color[i - 1] == y) color_segments--;
        if (color[i] == x && color[i + 1] == y) color_segments--;
    }

    for (int i = color_head[color_map[x]]; i; i = color_next[i]) {
        color[i] = y;
    }

    color_head[color_map[x]] = 0;
    color_count[color_map[y]] += color_count[color_map[x]];
    color_count[color_map[x]] = 0;
    color_map[x] = color_map[y];
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &color[i]);
        color_map[color[i]] = color[i];
    }

    init();

    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d %d", &x, &y);
            merge(x, y);
        } else if (op == 2) {
            printf("%d\n", color_segments);
        }
    }

    return 0;
}
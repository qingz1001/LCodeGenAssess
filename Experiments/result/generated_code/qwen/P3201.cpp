#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005
#define MAXM 100005

int n, m;
int colors[MAXN];
int segment_count[MAXN];

void update(int x, int y) {
    for (int i = 0; i < n; i++) {
        if (colors[i] == x) {
            colors[i] = y;
        }
    }
}

int count_segments() {
    int count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (colors[i] != colors[i + 1]) {
            count++;
        }
    }
    return count + 1;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &colors[i]);
    }

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            update(x, y);
        } else if (op == 2) {
            printf("%d\n", count_segments());
        }
    }

    return 0;
}